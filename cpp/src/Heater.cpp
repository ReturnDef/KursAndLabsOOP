#include "../include/Heater.hpp"
#include <cstdio>

Heater::Heater(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), temperature(20), mode(0) {
    std::printf("Heater '%s' инициализирован (id=%d)\n", getName().c_str(), getId());
}

Heater::Heater(const Heater& other)
    : Device(other), temperature(other.temperature), mode(other.mode) {}

Heater::~Heater() {}

void Heater::setTemperature(int t) {
    temperature = t;
    std::printf("Heater::setTemperature вызван для '%s', t=%d\n", getName().c_str(), temperature);
}

void Heater::setMode(int m) {
    mode = m;
    std::printf("Heater::setMode вызван для '%s', mode=%d\n", getName().c_str(), mode);
}

void Heater::scheduleTemperatureChange(std::time_t when, int temp) {
    std::printf("Heater::scheduleTemperatureChange для '%s' на %ld t=%d (демо)\n", getName().c_str(), (long)when, temp);
}

void Heater::showStatus() {
    std::printf("Heater '%s' статус: %s, temp=%d, mode=%d\n", getName().c_str(), state ? "ВКЛ" : "ВЫКЛ", temperature, mode);
}
