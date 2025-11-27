#include "../include/EnergyManager.hpp"
#include <cstdio>

EnergyManager::EnergyManager() {}

void EnergyManager::addMeter(std::shared_ptr<EnergyMeter> m) {
    if (m) {
        meters.push_back(m);
        std::printf("Добавлен счетчик: %s\n", m->getName().c_str());
    }
}

double EnergyManager::getEnergyReport() const {
    double sum = 0;
    for (auto m: meters) if (m) sum += m->getMonthlyReport();
    return sum;
}
