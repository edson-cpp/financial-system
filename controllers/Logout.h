#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Logout : public HttpController<Logout>
{
  public:
    void logout(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(Logout::logout, "/logout", Post);
    METHOD_LIST_END
};
