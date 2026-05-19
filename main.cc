#include <drogon/drogon.h>
#include <Database.h>
#include <filesystem>

int main() {
    namespace fs = std::filesystem;

    const char* configPath = std::getenv("CONFIG_PATH");

    fs::path projectRoot =
        fs::canonical("../");

    auto publicPath =
        (projectRoot / "public").string();

    auto viewsPath =
        (projectRoot / "views").string();
    
    if (!configPath){
        configPath = "../config.json";
    }

    Database::initialize();
    drogon::app()
        .setDocumentRoot(publicPath)
        .setUploadPath(publicPath + "/uploads")
        .addListener("127.0.0.1", 8081);
    drogon::app().loadConfigFile(configPath);
    drogon::app().run();
}