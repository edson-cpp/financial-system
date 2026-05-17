#include <drogon/drogon.h>
#include <Database.h>

int main() {
    Database::initialize();
    drogon::app().loadConfigFile("../config.json");
    drogon::app()
        .addListener("0.0.0.0", 8080)
        .setDocumentRoot("../")
        .run();
}