#include <drogon/drogon.h>
#include <Database.h>

int main() {
    Database::initialize();
    drogon::app().loadConfigFile("/home/edson/financial-system/config.json");
    drogon::app().run();
}