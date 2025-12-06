#include "Light.hpp"

Light::Light(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), brightness(0), color("white") {
    std::cout << "Свет '" << getName() << "' создан (id=" << getId() << ")" << std::endl;
}

Light::Light(const Light& other)
    : Device(other), brightness(other.brightness), color(other.color) {}

Light::~Light() {}

void Light::setBrightness(int b) {
    brightness = b;
    std::cout << "Свет '" << getName() << "' установлена яркость: " << brightness << std::endl;
}

void Light::setColor(const std::string &c) {
    color = c;
    std::cout << "Свет '" << getName() << "' установлен цвет: " << color << std::endl;
}

void Light::ecoMode() {
    std::cout << "Свет '" << getName() << "' эко-режим (демо)" << std::endl;
}

void Light::showStatus() {
    std::cout << "Свет '" << getName() << "' статус: " << (state ? "ВКЛ" : "ВЫКЛ") << ", яркость=" << brightness << std::endl;
}