#pragma once
#include "common.hpp"
#include "EnergyMeter.hpp"

class EnergyManager {
public:
    EnergyManager();
    void addMeter(std::shared_ptr<EnergyMeter> m);
    double getEnergyReport() const;

private:
    std::vector<std::shared_ptr<EnergyMeter>> meters;
};
