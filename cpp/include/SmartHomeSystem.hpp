#pragma once
#include <type_traits>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <numeric>
#include <algorithm>
#include "common.hpp"
#include "Device.hpp"
#include "Scenario.hpp"
#include "User.hpp"
#include "Scheduler.hpp"
#include "Notification.hpp"
#include "EnergyManager.hpp"

class SmartHomeSystem {
public:
    using DeviceEvent = std::function<void(std::shared_ptr<Device>)>;

    SmartHomeSystem();
    ~SmartHomeSystem();

    // devices
    void addDevice(std::shared_ptr<Device> d);
    void removeDevice(int id);
    std::shared_ptr<Device> findDevice(int id) const;

    // scenarios
    void addScenario(std::shared_ptr<Scenario> s);

    // users
    void addUser(std::shared_ptr<User> u);
    void removeUser(int id);
    std::shared_ptr<User> findUser(int id) const;
    std::vector<std::shared_ptr<User>> listUsers() const;

    // notifications
    void showNotifications() const;
    void sendNotificationToAll(const std::string& msg);
    void sendNotificationToDevice(int id, const std::string& msg);
    void clearNotifications();

    // energy
    EnergyManager& energy() { return energyManager; }
    double getTotalEnergyConsumption() const { return energyManager.getEnergyReport(); }

    // getters
    std::vector<std::shared_ptr<Scenario>> getScenarios() const { return scenarios; }
    std::vector<std::shared_ptr<Device>> getDevices() const { return devices; }

    // callbacks
    void onDeviceAdded(DeviceEvent cb) { deviceAddedCallbacks.push_back(cb); }
    void onDeviceRemoved(DeviceEvent cb) { deviceRemovedCallbacks.push_back(cb); }

private:
    std::vector<std::shared_ptr<Device>> devices;
    std::vector<std::shared_ptr<Scenario>> scenarios;
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Notification>> notifications;
    Scheduler scheduler;
    EnergyManager energyManager;

    std::vector<DeviceEvent> deviceAddedCallbacks;
    std::vector<DeviceEvent> deviceRemovedCallbacks;
};
