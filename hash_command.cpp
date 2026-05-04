#include <iostream>
#include <cstdlib>
#include <cstring>
#include <argon2.h>
#include <random>

std::string generateSalt(size_t size = 16) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 255);

    std::string salt;
    salt.resize(size);

    for (size_t i = 0; i < size; i++) {
        salt[i] = static_cast<char>(dist(gen));
    }

    return salt;
}

int main() {
    std::string userPassword = "P9L2rX$*SPOwmp";

    // Pepper stored in an environment variable.
    const char* pepperEnv = std::getenv("PASSWORD_PEPPER");

    if (!pepperEnv) {
        std::cerr << "PASSWORD_PEPPER not defined.\n";
        return 1;
    }

    std::string pepper = pepperEnv;

    // concatenate password + pepper
    std::string finalPassword = userPassword + pepper;

    // generates random salt
    std::string salt = generateSalt();

    // Argon2id parameters
    uint32_t t_cost = 3;        // iterations
    uint32_t m_cost = 65536;    // 64 MB
    uint32_t parallelism = 4;
    uint32_t hashLen = 32;

    char encoded[256];

    int result = argon2id_hash_encoded(
        t_cost,
        m_cost,
        parallelism,
        finalPassword.c_str(),
        finalPassword.length(),
        salt.data(),
        salt.size(),
        hashLen,
        encoded,
        sizeof(encoded)
    );

    if (result != ARGON2_OK) {
        std::cerr << "Error: " << argon2_error_message(result) << "\n";
        return 1;
    }

    std::cout << "Hash generated:\n" << encoded << std::endl;

    return 0;
}