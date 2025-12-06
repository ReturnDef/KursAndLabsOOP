#pragma once
#include "common.hpp"
#include <functional>
#include <vector>
#include <type_traits>
class Action;

class Device {
public:
    Device(int id = 0, const std::string &name = "", const std::string &location = "");
    Device(const Device& other);
    virtual ~Device() = default;

    virtual void turnOn();
    virtual void turnOff();
    virtual void showStatus();
    virtual void performAction(std::shared_ptr<Action> action);
    virtual double getEnergyUsage() const;
    virtual void updateFirmware();

    int getId() const;
    void setId(int id);

    std::string getName() const;
    void setName(const std::string &name);

    std::string getLocation() const;
    void setLocation(const std::string &location);

    bool getIsOnline() const;
    void setIsOnline(bool isOnline);

    double getPowerUsage() const;
    void setPowerUsage(double powerUsage);

    bool getState() const;
    void setState(bool state);

    Device& operator=(const Device& other) = default;

    virtual std::string getType() const { return "Device"; }

    void notify(const std::string& msg) {
        log(msg);
    }


public:
    using DeviceCallback = std::function<void(const Device&)>;
    void registerCallback(DeviceCallback cb);
    void unregisterCallbacks();
private:
    std::vector<DeviceCallback> callbacks;
public:
    template<typename T>
    requires std::is_arithmetic_v<T>
    void scalePower(T factor);

protected:
    void log(const std::string &msg) const;

    int id;
    std::string name;
    std::string location;
    bool isOnline;
    double powerUsage;
    bool state;
};
