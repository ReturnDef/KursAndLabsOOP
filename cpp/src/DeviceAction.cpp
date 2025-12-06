#include "DeviceAction.hpp"
#include <iostream>

DeviceAction::DeviceAction(const std::string& name,
                           std::shared_ptr<Device> dev,
                           Op op)
    : Action(name), device(dev), operation(op) {}

DeviceAction::DeviceAction(const DeviceAction& other)
    : Action(other), device(other.device), operation(other.operation) {}

void DeviceAction::execute() {
    if (device && operation) {
        operation(device);
        std::cout << "[DeviceAction] executed: " << name << std::endl;
    } else {
        std::cout << "[DeviceAction] FAILED: " << name
                  << " (no device or no operation)" << std::endl;
    }
}

std::shared_ptr<Action> DeviceAction::clone() const {
    return std::make_shared<DeviceAction>(*this);
}

void DeviceAction::modifyForScenario(const std::string &scenarioName) {
    if (device && scenarioName.find("Weekend") != std::string::npos) {
        double p = device->getPowerUsage();
        device->setPowerUsage(p * 0.9);
        device->notify("Сценарий изменил энергопотребление устройства");
    }
}
