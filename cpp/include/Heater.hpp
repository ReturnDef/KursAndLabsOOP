#pragma once
#include "Device.hpp"

class Heater : public Device {
public:
    Heater(int id = 0, const std::string &name = "Heater", const std::string &location = "");
    ~Heater();
    void setTemperature(int t);
    void setMode(const std::string &m);
    void scheduleTemperatureChange(std::time_t when, int temp);
    void showStatus() override;

private:
    int temperature;
    std::string mode;
};
