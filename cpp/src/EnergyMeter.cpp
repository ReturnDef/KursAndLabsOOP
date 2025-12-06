#include "EnergyMeter.hpp"

EnergyMeter::EnergyMeter(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), totalUsage(0.0) {
    std::cout << "Энергосчетчик '" << getName() << "' создан (id=" << getId() << ")" << std::endl;
}

EnergyMeter::EnergyMeter(const EnergyMeter& other)
    : Device(other), totalUsage(other.totalUsage) {}

EnergyMeter::~EnergyMeter() {}

void EnergyMeter::updateUsage(double amount) {
    totalUsage += amount;
    std::cout << "Энергосчетчик '" << getName() << "' обновлен на " << amount << std::endl;
}

double EnergyMeter::getMonthlyReport() const {
    return totalUsage;
}

void EnergyMeter::showStatus() {
    std::cout << "Энергосчетчик '" << getName() << "' общее потребление: " << totalUsage << std::endl;
}