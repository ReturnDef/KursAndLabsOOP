#pragma once
#include "Device.hpp"

class Camera : public Device {
public:
    Camera(int id = 0, const std::string &name = "Camera", const std::string &location = "");
    Camera(const Camera& other);
    ~Camera();
    void startRecording();
    void stopRecording();
    void saveRecording();
    void showStatus() override;

    Camera& operator=(const Device& base);

    std::string getType() const override { return "Camera"; }

private:
    bool isRecording;
};