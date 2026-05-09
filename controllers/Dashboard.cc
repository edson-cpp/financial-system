#include "Dashboard.h"

void Dashboard::index(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto session = req->session();

    if (!session->find("user_id"))
    {
        auto resp =
            HttpResponse::newRedirectionResponse("/login");

        callback(resp);
        return;
    }

    auto resp = HttpResponse::newHttpViewResponse("dashboard_page");
    callback(resp);
}
