#include "Notification.hpp"

Notification::Notification(int deviceId, const std::string &msg): deviceId(deviceId), message(msg), timestamp(std::time(nullptr)) {}

Notification::Notification(const std::string &msg): deviceId(-1), message(msg), timestamp(std::time(nullptr)) {}
Notification::Notification(const Notification& other): deviceId(other.deviceId), message(other.message), timestamp(other.timestamp) {}

void Notification::sendToDevice(int deviceId) {
    std::cout << "Уведомление для устройства " << deviceId << ": " << message << std::endl;
}

void Notification::sendToAllUsers() {
    std::cout << "Широковещательное уведомление: " << message << std::endl;
}

void Notification::show() const {
    std::cout << "[Уведомление] " << message << " (время: " << std::asctime(std::localtime(&timestamp)) << ")" << std::endl;
}
