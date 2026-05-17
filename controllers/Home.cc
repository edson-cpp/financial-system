#include "Home.h"

void Home::home(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback
)
{
    auto resp = HttpResponse::newHttpViewResponse("home.csp");

    callback(resp);
}