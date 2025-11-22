#include "../include/EnergyMeter.hpp"
#include <cstdio>

EnergyMeter::EnergyMeter(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), totalUsage(0.0) {}

EnergyMeter::~EnergyMeter() {}

void EnergyMeter::updateUsage(double amount) {
    totalUsage += amount;
    std::printf("Счетчик '%s' обновил потребление на %.2f\n", getName().c_str(), amount);
}

double EnergyMeter::getMonthlyReport() const {
    return totalUsage;
}

void EnergyMeter::showStatus() {
    std::printf("EnergyMeter '%s' общий расход: %.2f\n", getName().c_str(), totalUsage);
}
