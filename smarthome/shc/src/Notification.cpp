#include "Notification.hpp"

Notification::Notification(const std::string &msg): message(msg), timestamp(std::time(nullptr)) {}
Notification::Notification(const Notification& other): message(other.message), timestamp(other.timestamp) {}

void Notification::sendToDevice(int deviceId) {
    std::cout << "Уведомление для устройства " << deviceId << ": " << message << std::endl;
}

void Notification::sendToAllUsers() {
    std::cout << "Широковещательное уведомление: " << message << std::endl;
}

void Notification::show() const {
    std::cout << "[Уведомление] " << message << " (время: " << timestamp << ")" << std::endl;
}