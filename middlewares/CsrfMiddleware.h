#pragma once

#include <drogon/HttpMiddleware.h>
#include <drogon/drogon.h>

using namespace drogon;

class CsrfMiddleware : public HttpMiddleware<CsrfMiddleware>
{
  public:
    void invoke(
        const HttpRequestPtr &req,
        MiddlewareNextCallback &&next,
        MiddlewareCallback &&callback)
    {
        auto method = req->method();

        // Only protect methods that modify state.
        if (method == Post ||
            method == Put ||
            method == Delete)
        {
            auto session = req->session();

            // Token saved in the session
            auto sessionToken =
                session->getOptional<std::string>("csrf_token");

            if (!sessionToken)
            {
                auto resp =
                    HttpResponse::newHttpResponse();

                resp->setStatusCode(k403Forbidden);
                resp->setBody("CSRF token missing");

                callback(resp);
                return;
            }

            // Token sent via the form/header
            std::string requestToken =
                req->getParameter("csrf_token");

            // Alternative to APIs/AJAX
            if (requestToken.empty())
            {
                requestToken =
                    req->getHeader("X-CSRF-Token");
            }

            if (requestToken.empty() ||
                requestToken != *sessionToken)
            {
                auto resp =
                    HttpResponse::newHttpResponse();

                resp->setStatusCode(k403Forbidden);
                resp->setBody("Invalid CSRF token");

                callback(resp);
                return;
            }
        }

        next(req);
    }
};