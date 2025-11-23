#include "../include/SmartHomeSystem.hpp"

SmartHomeSystem::SmartHomeSystem() {}

void SmartHomeSystem::addDevice(Device* d) {
    if (d) {
        devices.push_back(d);
    }
}

void SmartHomeSystem::removeDevice(Device* d) {
    devices.erase(std::remove(devices.begin(), devices.end(), d), devices.end());
}

Device* SmartHomeSystem::findDeviceByName(const std::string &name) {
    for (auto d: devices) if (d && d->getName() == name) return d;
    return nullptr;
}

void SmartHomeSystem::runDemo() {
    for (auto d: devices) if (d) d->showStatus();
    scheduler.runPending();
}

EnergyManager& SmartHomeSystem::getEnergyManager() {
    return energyManager;
}

Scheduler& SmartHomeSystem::getScheduler() {
    return scheduler;
}