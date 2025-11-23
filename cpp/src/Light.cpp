#include "../include/Light.hpp"
#include <cstdio>

Light::Light(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), brightness(0), color("white") {}

Light::~Light() {}

void Light::setBrightness(int b) {
    brightness = b;
    std::printf("Light::setBrightness вызван для '%s', яркость=%d\n", getName().c_str(), brightness);
}

void Light::setColor(const std::string &c) {
    color = c;
    std::printf("Light::setColor вызван для '%s', цвет=%s\n", getName().c_str(), color.c_str());
}

void Light::ecoMode() {
    std::printf("Light::ecoMode вызван для '%s' (демо)\n", getName().c_str());
}

void Light::showStatus() {
    std::printf("Light '%s' в статусе: %s, яркость=%d\n", getName().c_str(), state ? "ВКЛ" : "ВЫКЛ", brightness);
}
