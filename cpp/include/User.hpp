#pragma once
#include "common.hpp"
#include "Scenario.hpp"

class User {
public:
    User(int id = 0, const std::string &name = "");
    User(const User& other);
    bool login(const std::string &username, const std::string &password);
    void logout();
    void executeScenario(std::shared_ptr<Scenario> s);
    void setPreference(const std::string &k, const std::string &v);

    int getUserId() const;

private:
    int userID;
    std::string name;
    std::string role;
    std::map<std::string, std::string> preferences;
};
