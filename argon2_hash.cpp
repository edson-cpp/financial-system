#include <iostream>
#include <cstdlib>
#include <cstring>
#include <argon2.h>
#include <random>
#include <termios.h>
#include <unistd.h>

// Desabilita echo para entrada de senha
std::string readPassword(const std::string& prompt) {
    std::cout << prompt;
    
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    std::getline(std::cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;

    return password;
}

std::string generateSalt(size_t size = 16) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 255);

    std::string salt(size, '\0');
    for (size_t i = 0; i < size; i++) {
        salt[i] = static_cast<char>(dist(gen));
    }

    return salt;
}

int main() {
    // leitura segura
    std::string userPassword = readPassword("Enter the user's password: ");
    std::string pepper = readPassword("Enter the pepper password: ");

    if (userPassword.empty()) {
        std::cerr << "User password cannot be empty.\n";
        return 1;
    }

    if (pepper.empty()) {
        std::cerr << "Pepper password cannot be empty.\n";
        return 1;
    }

    // concatena
    std::string finalPassword = userPassword + pepper;

    // gera salt
    std::string salt = generateSalt();

    // parâmetros Argon2id
    uint32_t t_cost = 3;
    uint32_t m_cost = 65536; // 64MB
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
        std::cerr << "Erro: " << argon2_error_message(result) << "\n";
        return 1;
    }

    std::cout << "Hash gerado:\n" << encoded << std::endl;

    // (opcional) limpar memória sensível
    std::fill(userPassword.begin(), userPassword.end(), '\0');
    std::fill(pepper.begin(), pepper.end(), '\0');
    std::fill(finalPassword.begin(), finalPassword.end(), '\0');

    return 0;
}