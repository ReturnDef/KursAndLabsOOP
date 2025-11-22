#pragma once
#include "Device.hpp"

class Camera : public Device {
public:
    Camera(int id = 0, const std::string &name = "Camera", const std::string &location = "");
    ~Camera();
    void startRecording();
    void stopRecording();
    void saveRecording();
    void showStatus() override;

private:
    bool isRecording;
};

