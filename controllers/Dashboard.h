#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Dashboard : public drogon::HttpController<Dashboard>
{
  public:
      METHOD_LIST_BEGIN
      ADD_METHOD_TO(Dashboard::index, "/dashboard", Get, "AuthFilter");
      METHOD_LIST_END

      void index(
          const HttpRequestPtr& req,
          std::function<void(const HttpResponsePtr&)>&& callback
      );
};
