#include <drogon/drogon.h>
#include <Database.h>
#include <filesystem>

int main() {
    namespace fs = std::filesystem;

    fs::path projectRoot;

    const char* envRoot = std::getenv("PROJECT_ROOT");

    projectRoot = envRoot ? fs::canonical(envRoot) : fs::canonical("./");
    /*if (envRoot)
    {
        projectRoot = fs::canonical(envRoot);
    }
    else
    {
        projectRoot = fs::canonical("../");
    }

    fs::path projectRoot = std::getenv("PROJECT_ROOT");

    if (projectRoot == ""){
        fs::path projectRoot = fs::canonical("./");
    }*/

    auto configPath =
        (projectRoot / "config.json").string();

    auto publicPath =
        (projectRoot / "public").string();

    auto viewsPath =
        (projectRoot / "views").string();
    
    Database::initialize();
    drogon::app()
        .setDocumentRoot(publicPath)
        .setUploadPath(publicPath + "/uploads")
        .addListener("127.0.0.1", 8081);
    drogon::app().loadConfigFile(configPath);
    drogon::app().run();
}