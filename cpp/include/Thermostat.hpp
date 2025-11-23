#pragma once
#include "Device.hpp"

class Thermostat : public Device {
public:
    Thermostat(int id = 0, const std::string &name = "Thermostat", const std::string &location = "");
    ~Thermostat();
    void setTargetTemp(double t);
    void setMode(const std::string &m);
    void autoAdjust();
    void showStatus() override;

private:
    double targetTemp;
    std::string mode;
};
