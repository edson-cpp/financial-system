#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Login : public HttpController<Login>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(Login::loginForm, "/login", Get);
    ADD_METHOD_TO(Login::loginUser, "/login", Post);
    METHOD_LIST_END

    void loginForm(const HttpRequestPtr &req,
                      std::function<void (const HttpResponsePtr &)> &&callback);

    void loginUser(const HttpRequestPtr &req,
                      std::function<void (const HttpResponsePtr &)> &&callback);
};