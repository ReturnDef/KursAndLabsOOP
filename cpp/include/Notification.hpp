#pragma once
#include "common.hpp"

class Notification {
public:
    Notification(const std::string &msg = "");
    void sendToDevice(const std::string &deviceId);
    void sendToAllUsers();
    void show() const;

private:
    std::string message;
    std::time_t timestamp;
};
