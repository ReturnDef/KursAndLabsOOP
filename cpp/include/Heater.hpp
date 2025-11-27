#pragma once
#include "Device.hpp"

class Heater : public Device {
public:
    Heater(int id = 0, const std::string &name = "Heater", const std::string &location = "");
    Heater(const Heater& other);
    ~Heater();
    void setTemperature(int t);
    void setMode(int m);
    void scheduleTemperatureChange(std::time_t when, int temp);
    void showStatus() override;

private:
    int temperature;
    int mode; // changed to int
};
