#include "SmartHomeSystem.hpp"
#include <iostream>

SmartHomeSystem::SmartHomeSystem() = default;
SmartHomeSystem::~SmartHomeSystem() = default;

void SmartHomeSystem::addDevice(std::shared_ptr<Device> d) {
    if (!d) return;
    // avoid duplicates by id
    auto it = std::find_if(devices.begin(), devices.end(), [&](const std::shared_ptr<Device>& x){
        return x && x->getId() == d->getId();
    });
    if (it == devices.end()) {
        devices.push_back(d);
        for (auto &cb : deviceAddedCallbacks) if (cb) cb(d);
    }
}

void SmartHomeSystem::removeDevice(int id) {
    auto it = std::remove_if(devices.begin(), devices.end(), [&](const std::shared_ptr<Device>& d){ return !d || d->getId() == id; });
    if (it != devices.end()) {
        // call callbacks for removed device(s)
        for (auto itr = it; itr != devices.end(); ++itr) {
            if (*itr) for (auto &cb : deviceRemovedCallbacks) if (cb) cb(*itr);
        }
        devices.erase(it, devices.end());
    }
}

std::shared_ptr<Device> SmartHomeSystem::findDevice(int id) const {
    auto it = std::find_if(devices.begin(), devices.end(), [&](auto &d){ return d && d->getId() == id; });
    return it==devices.end()? nullptr : *it;
}

void SmartHomeSystem::addScenario(std::shared_ptr<Scenario> s) {
    if (!s) return;
    scenarios.push_back(s);
    std::cout << "Добавлен сценарий: " << s->getName() << std::endl;
}

void SmartHomeSystem::addUser(std::shared_ptr<User> u) {
    if (!u) return;
    auto it = std::find_if(users.begin(), users.end(), [&](const std::shared_ptr<User>& x){ return x && x->getUserId() == u->getUserId(); });
    if (it == users.end()) {
        users.push_back(u);
        std::cout << "Добавлен пользователь: " << u->getName() << std::endl;
    }
}

void SmartHomeSystem::removeUser(int id) {
    auto it = std::remove_if(users.begin(), users.end(), [&](const std::shared_ptr<User>& u){ return !u || u->getUserId() == id; });
    if (it != users.end()) {
        users.erase(it, users.end());
        std::cout << "Пользователь с id=" << id << " удален" << std::endl;
    }
}

std::shared_ptr<User> SmartHomeSystem::findUser(int id) const {
    auto it = std::find_if(users.begin(), users.end(), [&](auto &u){ return u && u->getUserId() == id; });
    return it==users.end()? nullptr : *it;
}

std::vector<std::shared_ptr<User>> SmartHomeSystem::listUsers() const {
    return users;
}

void SmartHomeSystem::showNotifications() const {
    for (auto &n : notifications) if (n) n->show();
}

void SmartHomeSystem::sendNotificationToAll(const std::string& msg) {
    // push notification referencing no specific device
    notifications.push_back(std::make_shared<Notification>(msg));
    // also print to console
    std::cout << "Отправлено всем пользователям: " << msg << std::endl;
}

void SmartHomeSystem::sendNotificationToDevice(int id, const std::string& msg) {
    notifications.push_back(std::make_shared<Notification>(id, msg));
    std::cout << "Отправлено уведомление для устройства " << id << ": " << msg << std::endl;
}

void SmartHomeSystem::clearNotifications() {
    notifications.clear();
    std::cout << "Все уведомления удалены." << std::endl;
}
