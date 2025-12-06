#pragma once
#include "common.hpp"

class Notification {
public:
    Notification(int deviceId, const std::string &msg);
    Notification(const std::string &msg = "");
    Notification(const Notification& other);
    void sendToDevice(int deviceId);
    void sendToAllUsers();
    void show() const;

private:
    int deviceId = -1;
    std::string message;
    std::time_t timestamp;
};
