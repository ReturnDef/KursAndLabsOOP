#include "EnergyManager.hpp"
#include "NotificationCenter.hpp"
#include <numeric>

EnergyManager::EnergyManager() {}

void EnergyManager::addMeter(std::shared_ptr<EnergyMeter> m) {
    if (m) {
        meters.push_back(m);
        std::cout << "Добавлен счетчик: " << m->getName() << std::endl;
    }
}

double EnergyManager::getEnergyReport() const {
    double sum = 0.0;
    for (auto &m : meters) {
        if (m) sum += m->getMonthlyReport();
    }
    if (threshold > 0.0 && sum > threshold) {
        Notification n(std::string("Energy overuse detected: total=") + std::to_string(sum));
        NotificationCenter::instance().notify(n);
    }
    return sum;
}
