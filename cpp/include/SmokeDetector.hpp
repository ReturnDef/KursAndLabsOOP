#pragma once
#include "Device.hpp"

class SmokeDetector : public Device {
public:
    SmokeDetector(int id = 0, const std::string &name = "SmokeDetector", const std::string &location = "");
    SmokeDetector(const SmokeDetector& other);
    ~SmokeDetector();
    void detectSmoke(double level);
    void sendAlert();
    void showStatus() override;

private:
    double smokeLevel;
};
