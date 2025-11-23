#include "../include/Notification.hpp"
#include <cstdio>

Notification::Notification(const std::string &msg): message(msg), timestamp(std::time(nullptr)) {}

void Notification::sendToDevice(const std::string &deviceId) {
    std::printf("Уведомление для устройства %s: %s\n", deviceId.c_str(), message.c_str());
}

void Notification::sendToAllUsers() {
    std::printf("Рассылка всем пользователям: %s\n", message.c_str());
}

void Notification::show() const {
    std::printf("[Уведомление] %s (время: %ld)\n", message.c_str(), (long)timestamp);
}
