#pragma once
#include "common.hpp"
#include "EnergyMeter.hpp"

class EnergyManager {
public:
    EnergyManager();
    void addMeter(std::shared_ptr<EnergyMeter> m);
    double getEnergyReport() const;
    void setThreshold(double t) { threshold = t; }
    double getThreshold() const { return threshold; }

private:
    std::vector<std::shared_ptr<EnergyMeter>> meters;
    double threshold = 0.0;
};
