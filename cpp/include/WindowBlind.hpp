#pragma once
#include "Device.hpp"

class WindowBlind : public Device {
public:
    WindowBlind(int id = 0, const std::string &name = "WindowBlind", const std::string &location = "");
    ~WindowBlind();
    void open();
    void close();
    void setPosition(int p);
    void showStatus() override;

private:
    int position;
};
