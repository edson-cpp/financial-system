#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Home : public drogon::HttpController<Home>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(Home::home, "/", Get);
    METHOD_LIST_END

    void home(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback
    );
};