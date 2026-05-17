#pragma once

#include <drogon/orm/DbClient.h>

class Database
{
  public:
    static void initialize();

    static drogon::orm::DbClientPtr client();

  private:
    static drogon::orm::DbClientPtr dbClient_;
};