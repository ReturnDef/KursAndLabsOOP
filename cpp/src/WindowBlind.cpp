#include "../include/WindowBlind.hpp"
#include <cstdio>

WindowBlind::WindowBlind(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), position(0) {}

WindowBlind::~WindowBlind() {}

void WindowBlind::open() {
    position = 100;
    std::printf("WindowBlind::open для '%s'\n", getName().c_str());
}

void WindowBlind::close() {
    position = 0;
    std::printf("WindowBlind::close для '%s'\n", getName().c_str());
}

void WindowBlind::setPosition(int p) {
    position = p;
    std::printf("WindowBlind::setPosition для '%s' pos=%d\n", getName().c_str(), position);
}

void WindowBlind::showStatus() {
    std::printf("WindowBlind '%s' position=%d\n", getName().c_str(), position);
}
