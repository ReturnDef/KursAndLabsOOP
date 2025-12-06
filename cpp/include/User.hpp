#pragma once
#include "common.hpp"
#include "Scenario.hpp"

class User {
public:
    User(int id = 0, const std::string &name = "");
    User(const User& other);

    // authentication (demo)
    bool login(const std::string &username, const std::string &password);
    void logout();

    // scenarios
    void executeScenario(std::shared_ptr<Scenario> s);

    // preferences
    void setPreference(const std::string &k, const std::string &v);
    std::string getPreference(const std::string &k, const std::string &defaultValue = "") const;
    void resetPreferences();

    // id/name/role
    int getUserId() const;
    void setUserId(int id);
    std::string getName() const;
    void setName(const std::string &n);
    std::string getRole() const;
    void setRole(const std::string &r);

private:
    int userID = 0;
    std::string name;
    std::string role = "user";
    std::map<std::string, std::string> preferences;
};
