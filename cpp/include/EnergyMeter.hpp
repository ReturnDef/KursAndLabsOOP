#pragma once
#include "Device.hpp"

class EnergyMeter : public Device {
public:
    EnergyMeter(int id = 0, const std::string &name = "EnergyMeter", const std::string &location = "");
    EnergyMeter(const EnergyMeter& other);
    ~EnergyMeter();
    void updateUsage(double amount);
    double getMonthlyReport() const;
    void showStatus() override;

private:
    double totalUsage;
};
