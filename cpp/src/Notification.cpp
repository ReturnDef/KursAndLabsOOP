#include "../include/Notification.hpp"
#include <cstdio>

Notification::Notification(const std::string &msg): message(msg), timestamp(std::time(nullptr)) {}
Notification::Notification(const Notification& other): message(other.message), timestamp(other.timestamp) {}

void Notification::sendToDevice(int deviceId) {
    std::printf("Уведомление для устройства %d: %s\n", deviceId, message.c_str());
}

void Notification::sendToAllUsers() {
    std::printf("Рассылка всем пользователям: %s\n", message.c_str());
}

void Notification::show() const {
    std::printf("[Уведомление] %s (время: %ld)\n", message.c_str(), (long)timestamp);
}
