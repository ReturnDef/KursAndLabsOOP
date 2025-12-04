#include "User.hpp"

User::User(int id, const std::string &name): userID(id), name(name) {}
User::User(const User& other): userID(other.userID), name(other.name), role(other.role), preferences(other.preferences) {}

bool User::login(const std::string &username, const std::string &password) {
    std::cout << "Пользователь '" << username << "' вошел в систему (демо)" << std::endl;
    return true;
}

void User::logout() {
    std::cout << "Пользователь '" << name << "' вышел из системы" << std::endl;
}

void User::executeScenario(std::shared_ptr<Scenario> s) {
    if (s) {
        std::cout << "Пользователь '" << name << "' запускает сценарий '" << s->getName() << "'" << std::endl;
        s->execute();
    }
}

void User::setPreference(const std::string &k, const std::string &v) {
    preferences[k] = v;
    std::cout << "Установлена настройка '" << k << "'='" << v << "' для пользователя '" << name << "'" << std::endl;
}

int User::getUserId() const { 
    return userID; 
}