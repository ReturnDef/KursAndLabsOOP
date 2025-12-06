#include "Camera.hpp"

Camera::Camera(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), isRecording(false) {
    std::cout << "Камера '" << getName() << "' создана (id=" << getId() << ")" << std::endl;
}

Camera::Camera(const Camera& other)
    : Device(other), isRecording(other.isRecording) {}

Camera::~Camera() {}

void Camera::startRecording() {
    isRecording = true;
    log("Вызвана запись");
}

void Camera::stopRecording() {
    isRecording = false;
    log("Запись остановлена");
}

void Camera::saveRecording() {
    log("Запись сохранена");
}

void Camera::showStatus() {
    std::cout << "Камера '" << getName() << "' запись: " << (isRecording ? "ДА" : "НЕТ") << std::endl;
}

Camera& Camera::operator=(const Device& base) {
    if (this == &base) return *this;
    this->Device::operator=(base);
    this->isRecording = false;
    log("Назначено из устройства");
    return *this;
}