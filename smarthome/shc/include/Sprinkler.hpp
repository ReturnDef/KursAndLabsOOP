#pragma once
#include "Device.hpp"

class Sprinkler : public Device {
public:
    Sprinkler(int id = 0, const std::string &name = "Sprinkler", const std::string &location = "");
    Sprinkler(const Sprinkler& other);
    ~Sprinkler();
    void turnOnSprinkler();
    void turnOffSprinkler();
    void scheduleWatering(std::time_t when);
    void showStatus() override;

private:
    double flowRate;
};
