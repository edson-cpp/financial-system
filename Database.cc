#include "Database.h"

#include <cstdlib>
#include <stdexcept>

drogon::orm::DbClientPtr Database::dbClient_;

void Database::initialize()
{
    const char* password = std::getenv("DB_PASSWORD");

    if (!password)
    {
        throw std::runtime_error("DB_PASSWORD not set");
    }

    std::string connInfo =
    "host=127.0.0.1 "
    "port=3306 "
    "dbname=financial_system "
    "user=eds "
    "password=" + std::string(password);

    dbClient_ = drogon::orm::DbClient::newMysqlClient(
        connInfo,
        4
    );
}

drogon::orm::DbClientPtr Database::client()
{
    return dbClient_;
}