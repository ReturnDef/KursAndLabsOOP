#include "Heater.hpp"

Heater::Heater(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), temperature(20), mode(0) {
    std::cout << "Обогреватель '" << getName() << "' инициализирован (id=" << getId() << ")" << std::endl;
}

Heater::Heater(const Heater& other)
    : Device(other), temperature(other.temperature), mode(other.mode) {}

Heater::~Heater() {}

void Heater::setTemperature(int t) {
    temperature = t;
    std::cout << "Обогреватель '" << getName() << "' установлена температура: " << temperature << std::endl;
}

void Heater::setMode(int m) {
    mode = m;
    std::cout << "Обогреватель '" << getName() << "' установлен режим: " << mode << std::endl;
}

void Heater::scheduleTemperatureChange(std::time_t when, int temp) {
    std::cout << "Обогреватель '" << getName() << "' запланировано изменение температуры на " << when << " до " << temp << " (демо)" << std::endl;
}

void Heater::showStatus() {
    std::cout << "Обогреватель '" << getName() << "' статус: " << (state ? "ВКЛ" : "ВЫКЛ") << ", температура=" << temperature << ", режим=" << mode << std::endl;
}