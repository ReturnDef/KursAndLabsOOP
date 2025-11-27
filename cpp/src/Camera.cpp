#include "../include/Camera.hpp"
#include <cstdio>

Camera::Camera(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), isRecording(false) {
    std::printf("Camera '%s' создана (id=%d)\n", getName().c_str(), getId());
}

Camera::Camera(const Camera& other)
    : Device(other), isRecording(other.isRecording) {}

Camera::~Camera() {}

void Camera::startRecording() {
    isRecording = true;
    std::printf("Camera::startRecording вызван для '%s'\n", getName().c_str());
}

void Camera::stopRecording() {
    isRecording = false;
    std::printf("Camera::stopRecording вызван для '%s'\n", getName().c_str());
}

void Camera::saveRecording() {
    std::printf("Camera::saveRecording вызван для '%s'\n", getName().c_str());
}

void Camera::showStatus() {
    std::printf("Camera '%s' recording: %s\n", getName().c_str(), isRecording ? "ДА" : "НЕТ");
}
