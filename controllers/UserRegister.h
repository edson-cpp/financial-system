#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class UserRegister : public HttpController<UserRegister>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserRegister::registerForm, "/register", Get, "AuthFilter");
    ADD_METHOD_TO(UserRegister::registerUser, "/register", Post);
    ADD_METHOD_TO(UserRegister::registerContent, "/register/content", Get);
    METHOD_LIST_END

    void registerForm(const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback);

    void registerUser(const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback);

    void registerContent(const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback);

    
};