#pragma once
#include "Device.hpp"

class Thermostat : public Device {
public:
    Thermostat(int id = 0, const std::string &name = "Thermostat", const std::string &location = "");
    Thermostat(const Thermostat& other);
    ~Thermostat();
    void setTargetTemp(double t);
    void setMode(int m);
    void autoAdjust();
    void showStatus() override;

private:
    double targetTemp;
    int mode;
};
