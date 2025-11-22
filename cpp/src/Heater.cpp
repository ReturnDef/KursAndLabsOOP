#include "../include/Heater.hpp"
#include <cstdio>

Heater::Heater(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), temperature(20), mode("off") {}

Heater::~Heater() {}

void Heater::setTemperature(int t) {
    temperature = t;
    std::printf("Heater::setTemperature вызван для '%s', t=%d\n", getName().c_str(), temperature);
}

void Heater::setMode(const std::string &m) {
    mode = m;
    std::printf("Heater::setMode вызван для '%s', mode=%s\n", getName().c_str(), mode.c_str());
}

void Heater::scheduleTemperatureChange(std::time_t when, int temp) {
    std::printf("Heater::scheduleTemperatureChange для '%s' на %ld t=%d (демо)\n", getName().c_str(), (long)when, temp);
}

void Heater::showStatus() {
    std::printf("Heater '%s' статус: %s, temp=%d\n", getName().c_str(), state ? "ВКЛ" : "ВЫКЛ", temperature);
}
