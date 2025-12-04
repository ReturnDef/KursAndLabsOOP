#include "EnergyManager.hpp"

EnergyManager::EnergyManager() {}

void EnergyManager::addMeter(std::shared_ptr<EnergyMeter> m) {
    if (m) {
        meters.push_back(m);
        std::cout << "Добавлен счетчик: " << m->getName() << std::endl;
    }
}

double EnergyManager::getEnergyReport() const {
    double sum = 0;
    for (auto m: meters) if (m) sum += m->getMonthlyReport();
    return sum;
}