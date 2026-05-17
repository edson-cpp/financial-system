#include "Login.h"
#include <argon2.h>
#include "../middlewares/LoginRateLimitMiddleware.h"
#include <Database.h>

using namespace drogon;

void Login::loginForm(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto session = req->session();

    if (session->find("user_id"))
    {
        auto resp =
            HttpResponse::newRedirectionResponse("/dashboard");

        callback(resp);
        return;
    }

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

    auto db = Database::client();

    db->execSqlAsync(
        "SELECT users_id, pwd FROM users WHERE login = ?",
        [callback, pwd, req](const orm::Result& r) {
            if (r.empty()) {
                auto resp = HttpResponse::newHttpResponse();
                resp->setBody("User not found"); // later: redirect
                callback(resp);
                return;
            }

            const char* pepperEnv = std::getenv("PASSWORD_PEPPER");
            std::string pepper = pepperEnv;
            std::string finalPwd = pwd + pepper;

            int userId = r[0]["users_id"].as<int>();
            std::string hash = r[0]["pwd"].as<std::string>();


            if (argon2id_verify(hash.c_str(), finalPwd.c_str(), finalPwd.size()) == ARGON2_OK) {
                auto session = req->session();

                session->insert("user_id", userId);

                std::string csrfToken = utils::getUuid();
                session->insert("csrf_token", csrfToken);
                HttpViewData data;
                data.insert("csrf_token", csrfToken);

                std::string redirectTo = "/dashboard";

                if (session->find("redirect_after_login"))
                {
                    redirectTo =
                        session->get<std::string>(
                            "redirect_after_login"
                        );

                    session->erase("redirect_after_login");
                }

                LoginRateLimitMiddleware::resetAttempts(req->peerAddr().toIp());
                auto resp = HttpResponse::newRedirectionResponse(redirectTo);

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