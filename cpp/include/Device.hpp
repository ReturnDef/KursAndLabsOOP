#pragma once
#include "common.hpp"

class Action;

class Device {
public:
    Device(int id = 0, const std::string &name = "", const std::string &location = "");
    virtual ~Device();

    virtual void turnOn();
    virtual void turnOff();
    virtual void showStatus();
    virtual void performAction(Action* action);
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

protected:
    int id;
    std::string name;
    std::string location;
    bool isOnline;
    double powerUsage;
    bool state;
};
