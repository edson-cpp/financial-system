#include <drogon/drogon.h>
#include <Database.h>

int main() {
    const char* configPath = std::getenv("CONFIG_PATH");

    if (!configPath){
        configPath = "../config.json";
    }

    Database::initialize();
    drogon::app().loadConfigFile(configPath);
    drogon::app().run();
}