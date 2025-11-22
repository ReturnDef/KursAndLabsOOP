#pragma once
#include "common.hpp"
#include "EnergyMeter.hpp"

class EnergyManager {
public:
    EnergyManager();
    void addMeter(EnergyMeter* m);
    double getEnergyReport() const;

private:
    std::vector<EnergyMeter*> meters;
};
