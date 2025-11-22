#pragma once
#include "Device.hpp"

class Light : public Device {
public:
    Light(int id = 0, const std::string &name = "Light", const std::string &location = "");
    ~Light();
    void setBrightness(int b);
    void setColor(const std::string &c);
    void ecoMode();
    void showStatus() override;

private:
    int brightness;
    std::string color;
};
