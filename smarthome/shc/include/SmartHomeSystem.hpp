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
    ~SmartHomeSystem();

    SmartHomeSystem(const SmartHomeSystem&) = delete;
    SmartHomeSystem& operator=(const SmartHomeSystem&) = delete;

    void addDevice(std::shared_ptr<Device> d);
    void removeDevice(std::shared_ptr<Device> d);
    std::shared_ptr<Device> findDeviceByName(const std::string &name);
    void runDemo();

    void addAction(std::shared_ptr<Action> a);
    std::shared_ptr<Action> findAction(const std::string &name) const;

    void addScenario(std::shared_ptr<Scenario> s);
    std::shared_ptr<Scenario> findScenario(const std::string &name) const;

    void addUser(std::shared_ptr<User> u);
    std::shared_ptr<User> findUser(int id) const;

    void showDevices() const;
    void showScenarios() const;
    void showActions() const;

    void sendNotificationToDevice(int deviceId, const std::string &msg);
    void sendNotificationToAll(const std::string &msg);
    void showNotifications() const;

    EnergyManager& getEnergyManager();
    Scheduler& getScheduler();

    std::shared_ptr<Scenario> duplicateScenario(const std::string& existingName,
                                                const std::string& newName,
                                                bool deepCopy);

private:
    std::vector<std::shared_ptr<Device>> devices;
    std::vector<std::shared_ptr<Scenario>> scenarios;
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Action>> actions;
    std::vector<std::shared_ptr<Notification>> notifications;
    EnergyManager energyManager;
    Scheduler scheduler;
};
