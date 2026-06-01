#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Menu : public drogon::HttpController<Menu>
{
  public:
      METHOD_LIST_BEGIN
      ADD_METHOD_TO(Menu::index, "/menu", Get, "AuthFilter");
      METHOD_LIST_END

      void index(
          const HttpRequestPtr& req,
          std::function<void(const HttpResponsePtr&)>&& callback
      );
};
