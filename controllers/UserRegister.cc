#include "UserRegister.h"
#include "../hash.cpp"
#include <Database.h>

using namespace drogon;

void UserRegister::registerForm(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpViewResponse("register_page");
    callback(resp);
}

void UserRegister::registerUser(
    const HttpRequestPtr &req,
    std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto params = req->getParameters();

    std::string name = params["name"];
    std::string login = params["login"];
    std::string pwd = params["pwd"];
    std::string national_id = params["national_id"];
    std::string national_id_type = params["national_id_type"];
    std::string country_code = params["country_code"];
    std::string phone = params["phone"];
    std::string email = params["email"];
    std::uint8_t level = 1; //static_cast<uint8_t>(std::stoi(params["level"]));

    std::string hashedPassword = getHash(pwd);

    auto dbClient = Database::client();

    dbClient->execSqlAsync(
        R"(INSERT INTO users (name, login, pwd, national_id, national_id_type, 
            country_code, phone, email, level) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?))",
        [callback](const orm::Result &result) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody("User saved!");
            callback(resp);
        },
        [callback](const orm::DrogonDbException &e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody(std::string("DB Error: ") + e.base().what());
            callback(resp);
        },
        name, login, hashedPassword, national_id, national_id_type, country_code, phone, email, level
    );
}
