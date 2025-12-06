#pragma once
#include <string>
#include <vector>
#include <functional>
#include <map>

struct SimpleDevice {
    int id;
    std::string name;
    bool on = false;
    std::map<std::string,std::string> props;
};

struct SimpleScenario {
    int id;
    std::string name;
    std::vector<std::function<void()>> actions;
};

class SmartHomeController {
    std::vector<SimpleDevice> devices;
    std::vector<SimpleScenario> scenarios;
    std::vector<std::string> logs;
    int nextDeviceId = 1;
    int nextScenarioId = 1;
public:
    // Devices
    int addDevice(const std::string &name);
    bool removeDevice(int id);
    SimpleDevice* findDeviceById(int id);
    SimpleDevice* findDeviceByName(const std::string &name);
    std::vector<SimpleDevice>& listDevices();

    // Scenarios
    int addScenario(const std::string &name);
    SimpleScenario* getScenario(int id);
    std::vector<SimpleScenario>& listScenarios();
    void runScenario(int id);

    // Logs
    void log(const std::string &msg);
    const std::vector<std::string>& getLogs() const;
};
