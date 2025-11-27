#pragma once
#include "common.hpp"

class Notification {
public:
    Notification(const std::string &msg = "");
    Notification(const Notification& other);
    void sendToDevice(int deviceId);
    void sendToAllUsers();
    void show() const;

private:
    std::string message;
    std::time_t timestamp;
};
