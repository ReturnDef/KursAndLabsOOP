#include "SmartHomeSystem.hpp"

SmartHomeSystem::SmartHomeSystem() {}
SmartHomeSystem::~SmartHomeSystem() {}

void SmartHomeSystem::addDevice(std::shared_ptr<Device> d) {
    if (d) devices.push_back(d);
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
    std::cout << "\n=== Устройства ===" << std::endl;
    for (auto d: devices) if (d) std::cout << "id=" << d->getId() << ", имя=" << d->getName() << ", локация=" << d->getLocation() << std::endl;
}

void SmartHomeSystem::showScenarios() const {
    std::cout << "\n=== Сценарии ===" << std::endl;
    for (auto s: scenarios) if (s) std::cout << s->getName() << std::endl;
}

void SmartHomeSystem::showActions() const {
    std::cout << "\n=== Действия ===" << std::endl;
    for (auto a: actions) if (a) std::cout << a->getName() << std::endl;
}

void SmartHomeSystem::sendNotificationToDevice(int deviceId, const std::string &msg) {
    auto n = std::make_shared<Notification>(msg);
    notifications.push_back(n);
    std::cout << "[Уведомление] устройству " << deviceId << ": " << msg << std::endl;
}

void SmartHomeSystem::sendNotificationToAll(const std::string &msg) {
    auto n = std::make_shared<Notification>(msg);
    notifications.push_back(n);
    std::cout << "[Уведомление] ВСЕМ: " << msg << std::endl;
}

void SmartHomeSystem::showNotifications() const {
    std::cout << "\n=== Журнал уведомлений ===" << std::endl;
    for (auto n: notifications) if (n) n->show();
}

EnergyManager& SmartHomeSystem::getEnergyManager() {
    return energyManager;
}

Scheduler& SmartHomeSystem::getScheduler() {
    return scheduler;
}

std::shared_ptr<Scenario> SmartHomeSystem::duplicateScenario(const std::string& existingName,
                                                             const std::string& newName,
                                                             bool deepCopy)
{
    auto s = findScenario(existingName);
    if (!s) return nullptr;

    auto copy = deepCopy ? s->cloneDeep() : s->cloneShallow();
    copy->adaptTo(newName);
    scenarios.push_back(copy);
    std::cout << "Сценарий '" << existingName << "' скопирован как '" << newName << "' (глубокое=" << deepCopy << ")" << std::endl;
    return copy;
}