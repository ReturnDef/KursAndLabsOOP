#include "../include/Thermostat.hpp"
#include <cstdio>

Thermostat::Thermostat(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), targetTemp(20.0), mode("auto") {}

Thermostat::~Thermostat() {}

void Thermostat::setTargetTemp(double t) {
    targetTemp = t;
    std::printf("Thermostat::setTargetTemp для '%s' t=%.1f\n", getName().c_str(), targetTemp);
}

void Thermostat::setMode(const std::string &m) {
    mode = m;
    std::printf("Thermostat::setMode для '%s' mode=%s\n", getName().c_str(), mode.c_str());
}

void Thermostat::autoAdjust() {
    std::printf("Thermostat::autoAdjust для '%s' (демо)\n", getName().c_str());
}

void Thermostat::showStatus() {
    std::printf("Thermostat '%s' target=%.1f mode=%s\n", getName().c_str(), targetTemp, mode.c_str());
}
