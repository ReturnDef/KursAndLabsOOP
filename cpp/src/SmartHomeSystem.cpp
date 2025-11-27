#include "../include/SmartHomeSystem.hpp"
#include <algorithm>
#include <cstdio>

SmartHomeSystem::SmartHomeSystem() {}

void SmartHomeSystem::addDevice(std::shared_ptr<Device> d) {
    if (d) {
        devices.push_back(d);
    }
}

void SmartHomeSystem::removeDevice(std::shared_ptr<Device> d) {
    devices.erase(std::remove(devices.begin(), devices.end(), d), devices.end());
}

std::shared_ptr<Device> SmartHomeSystem::findDeviceByName(const std::string &name) {
    for (auto d: devices) if (d && d->getName() == name) return d;
    return nullptr;
}

void SmartHomeSystem::runDemo() {
    for (auto d: devices) if (d) d->showStatus();
    scheduler.runPending();
}

void SmartHomeSystem::addAction(std::shared_ptr<Action> a) {
    if (a) actions.push_back(a);
}

std::shared_ptr<Action> SmartHomeSystem::findAction(const std::string &name) const {
    for (auto a: actions) if (a && a->getName() == name) return a;
    return nullptr;
}

void SmartHomeSystem::addScenario(std::shared_ptr<Scenario> s) {
    if (s) scenarios.push_back(s);
}

std::shared_ptr<Scenario> SmartHomeSystem::findScenario(const std::string &name) const {
    for (auto s: scenarios) if (s && s->getName() == name) return s;
    return nullptr;
}

void SmartHomeSystem::addUser(std::shared_ptr<User> u) {
    if (u) users.push_back(u);
}

std::shared_ptr<User> SmartHomeSystem::findUser(int id) const {
    for (auto u: users) if (u && u->getUserId() == id) return u;
    return nullptr;
}

void SmartHomeSystem::showDevices() const {
    std::printf("\n=== Устройства ===\n");
    for (auto d: devices) if (d) std::printf("id=%d, name=%s, loc=%s\n", d->getId(), d->getName().c_str(), d->getLocation().c_str());
}

void SmartHomeSystem::showScenarios() const {
    std::printf("\n=== Сценарии ===\n");
    for (auto s: scenarios) if (s) std::printf("%s\n", s->getName().c_str());
}

void SmartHomeSystem::showActions() const {
    std::printf("\n=== Действия ===\n");
    for (auto a: actions) if (a) std::printf("%s\n", a->getName().c_str());
}

void SmartHomeSystem::sendNotificationToDevice(int deviceId, const std::string &msg) {
    auto n = std::make_shared<Notification>(msg);
    notifications.push_back(n);
    std::printf("[Уведомление] для устройства %d: %s\n", deviceId, msg.c_str());
}

void SmartHomeSystem::sendNotificationToAll(const std::string &msg) {
    auto n = std::make_shared<Notification>(msg);
    notifications.push_back(n);
    std::printf("[Уведомление] всем: %s\n", msg.c_str());
}

void SmartHomeSystem::showNotifications() const {
    std::printf("\n=== Журнал уведомлений ===\n");
    for (auto n: notifications) if (n) n->show();
}

EnergyManager& SmartHomeSystem::getEnergyManager() {
    return energyManager;
}

Scheduler& SmartHomeSystem::getScheduler() {
    return scheduler;
}
