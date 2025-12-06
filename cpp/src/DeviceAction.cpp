#include "DeviceAction.hpp"

DeviceAction::DeviceAction(const std::string& name, std::shared_ptr<Device> dev, Op op)
    : Action(name), device(dev), operation(op) {}

DeviceAction::DeviceAction(const DeviceAction& other)
    : Action(other), device(other.device), operation(other.operation) {}

void DeviceAction::execute() {
    if (device && operation) {
        operation(device);
        std::cout << "Действие устройства выполнено: " << name << std::endl;
    } else {
        std::cout << "Действие устройства не выполнено (нет устройства или операции): " << name << std::endl;
    }
}

std::shared_ptr<Action> DeviceAction::clone() const {
    return std::make_shared<DeviceAction>(*this);
}

void DeviceAction::modifyForScenario(const std::string &scenarioName) {
    if (device && scenarioName.find("Weekend") != std::string::npos) {
        double pu = device->getPowerUsage();
        device->setPowerUsage(pu * 0.9);
        device->notify("Действие выполнено");
    }
}