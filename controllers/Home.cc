#include "Home.h"

void Home::home(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback
)
{
    auto session = req->session();

    if (session->find("user_id"))
    {
        auto resp = HttpResponse::newRedirectionResponse("/dashboard");

        callback(resp);
        return;
    }

    auto resp = HttpResponse::newHttpViewResponse("home.csp");

    callback(resp);
}