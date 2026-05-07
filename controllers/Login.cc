#include "Login.h"
#include <argon2.h>

using namespace drogon;

void Login::loginForm(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpViewResponse("login");
    callback(resp);
}

void Login::loginUser(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto params = req->getParameters();

    auto login = params["login"];
    auto pwd = params["pwd"];

    auto db = app().getDbClient();

    db->execSqlAsync(
        "SELECT pwd FROM users WHERE login = ?",
        [callback, pwd](const orm::Result& r) {
            if (r.empty()) {
                auto resp = HttpResponse::newHttpResponse();
                resp->setBody("User not found"); // later: redirect
                callback(resp);
                return;
            }

            const char* pepperEnv = std::getenv("PASSWORD_PEPPER");
            std::string pepper = pepperEnv;
            std::string finalPwd = pwd + pepper;

            std::string hash = r[0]["pwd"].as<std::string>();


            if (argon2id_verify(hash.c_str(), finalPwd.c_str(), finalPwd.size()) == ARGON2_OK) {
                auto resp = HttpResponse::newHttpResponse();
                resp->setBody("Login OK"); // later: redirect
                callback(resp);
            } else {
                auto resp = HttpResponse::newHttpResponse();
                resp->setBody("Invalid password");
                callback(resp);
            }
        },
        [callback](const orm::DrogonDbException& e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("DB error");
            callback(resp);
        },
        login
    );
}