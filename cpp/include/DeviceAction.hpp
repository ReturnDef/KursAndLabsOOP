#pragma once
#include "Action.hpp"
#include "Device.hpp"
#include <memory>
#include <functional>

class DeviceAction : public Action {
public:
    using Op = std::function<void(std::shared_ptr<Device>)>;

    DeviceAction(const std::string& name, std::shared_ptr<Device> dev, Op op);
    DeviceAction(const DeviceAction& other);

    void execute() override;
    std::shared_ptr<Action> clone() const override;
    void modifyForScenario(const std::string &scenarioName) override;

    // 🔥 Геттер устройства (добавлено)
    std::shared_ptr<Device> getDevice() const { return device; }

private:
    std::shared_ptr<Device> device;
    Op operation;
};
