#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Dashboard : public HttpController<Dashboard>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(Dashboard::dashboardForm, "/dashboard", Get, "AuthFilter");
    ADD_METHOD_TO(Dashboard::dashboardContent, "/dashboard/content", Get);
    METHOD_LIST_END

    void dashboardForm(const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback);

    void dashboardContent(const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback);

    
};