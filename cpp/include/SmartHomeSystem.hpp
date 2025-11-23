#pragma once
#include "common.hpp"
#include "Device.hpp"
#include "Scenario.hpp"
#include "User.hpp"
#include "Scheduler.hpp"
#include "Notification.hpp"
#include "EnergyManager.hpp"

class SmartHomeSystem {
public:
    SmartHomeSystem();
    void addDevice(Device* d);
    void removeDevice(Device* d);
    Device* findDeviceByName(const std::string &name);
    void runDemo();

    // Геттеры для доступа к private членам
    EnergyManager& getEnergyManager();
    Scheduler& getScheduler();

private:
    std::vector<Device*> devices;
    std::vector<Scenario*> scenarios;
    std::vector<User*> users;
    EnergyManager energyManager;
    Scheduler scheduler;
};