#pragma once
#include "common.hpp"
#include "Scenario.hpp"

class User {
public:
    User(const std::string &id = "", const std::string &name = "");
    bool login(const std::string &username, const std::string &password);
    void logout();
    void executeScenario(Scenario* s);
    void setPreference(const std::string &k, const std::string &v);

private:
    std::string userID;
    std::string name;
    std::string role;
    std::map<std::string, std::string> preferences;
};
