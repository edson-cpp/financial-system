#include "Dashboard.h"

using namespace drogon;

void Dashboard::dashboardForm(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newRedirectionResponse("/menu?page=dashboard");
    callback(resp);
}

void Dashboard::dashboardContent(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpViewResponse("dashboard");
    callback(resp);
}
