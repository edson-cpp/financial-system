#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UserRegister : public HttpController<UserRegister>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserRegister::registerForm, "/register", Get);
    ADD_METHOD_TO(UserRegister::registerUser, "/register", Post);
    METHOD_LIST_END

    void registerForm(const HttpRequestPtr &req,
                      std::function<void (const HttpResponsePtr &)> &&callback);

    void registerUser(const HttpRequestPtr &req,
                      std::function<void (const HttpResponsePtr &)> &&callback);
};