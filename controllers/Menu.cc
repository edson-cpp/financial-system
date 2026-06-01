#include "Menu.h"

void Menu::index(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto session = req->session();

    if (!session->find("user_id"))
    {
        auto resp = HttpResponse::newRedirectionResponse("/login");

        callback(resp);
        return;
    }

    auto resp = HttpResponse::newHttpViewResponse("menu");
    callback(resp);
}
