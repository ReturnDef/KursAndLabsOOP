#include "../include/User.hpp"
#include <cstdio>

User::User(const std::string &id, const std::string &name): userID(id), name(name) {}

bool User::login(const std::string &username, const std::string &password) {
    std::printf("Пользователь '%s' вошёл в систему (демо)\n", username.c_str());
    return true;
}

void User::logout() {
    std::printf("Пользователь '%s' вышел\n", name.c_str());
}

void User::executeScenario(Scenario* s) {
    if (s) {
        std::printf("Пользователь '%s' запускает сценарий '%s'\n", name.c_str(), s->getName().c_str());
        s->execute();
    }
}

void User::setPreference(const std::string &k, const std::string &v) {
    preferences[k] = v;
    std::printf("Установлена настройка '%s' = '%s' для пользователя '%s'\n", k.c_str(), v.c_str(), name.c_str());
}
