#include "Thermostat.hpp"

Thermostat::Thermostat(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), targetTemp(20.0), mode(0) {}

Thermostat::Thermostat(const Thermostat& other)
    : Device(other), targetTemp(other.targetTemp), mode(other.mode) {}

Thermostat::~Thermostat() {}

void Thermostat::setTargetTemp(double t) {
    targetTemp = t;
    std::cout << "Термостат '" << getName() << "' установлена температура: " << targetTemp << std::endl;
}

void Thermostat::setMode(int m) {
    mode = m;
    std::cout << "Термостат '" << getName() << "' установлен режим: " << mode << std::endl;
}

void Thermostat::autoAdjust() {
    std::cout << "Термостат '" << getName() << "' авторегулировка (демо)" << std::endl;
}

void Thermostat::showStatus() {
    std::cout << "Термостат '" << getName() << "' целевая температура=" << targetTemp << " режим=" << mode << std::endl;
}