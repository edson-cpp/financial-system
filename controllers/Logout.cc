#include "Logout.h"

void Logout::logout(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto session = req->session();

    session->erase("user_id");
    session->clear();

    auto resp = HttpResponse::newRedirectionResponse("/");
    callback(resp);
}