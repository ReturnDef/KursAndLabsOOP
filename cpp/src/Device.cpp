#include <algorithm>
#include "Device.hpp"

Device::Device(int id, const std::string &name, const std::string &location)
    : id(id), name(name), location(location), isOnline(true), powerUsage(0.0), state(false) {}

Device::Device(const Device& other)
    : id(other.id), name(other.name), location(other.location), isOnline(other.isOnline),
      powerUsage(other.powerUsage), state(other.state) {}

void Device::turnOn() {
    state = true;
    std::cout << "Устройство '" << name << "' включено" << std::endl;
}

void Device::turnOff() {
    state = false;
    std::cout << "Устройство '" << name << "' выключено" << std::endl;
}

void Device::showStatus() {
    std::cout << "Статус '" << name << "': " << (state ? "ВКЛ" : "ВЫКЛ") << ", местоположение=" << location << std::endl;
}

void Device::performAction(std::shared_ptr<Action> /*action*/) {
    std::cout << "Устройство '" << name << "' выполняет базовое действие" << std::endl;
}

double Device::getEnergyUsage() const {
    return powerUsage;
}

void Device::updateFirmware() {
    std::cout << "Обновление прошивки для '" << name << "' (демо)" << std::endl;
}

int Device::getId() const { 
    return id; 
}

void Device::setId(int id) { 
    this->id = id; 
}

std::string Device::getName() const { 
    return name; 
}

void Device::setName(const std::string &name) { 
    this->name = name; 
}

std::string Device::getLocation() const { 
    return location; 
}

void Device::setLocation(const std::string &location) { 
    this->location = location; 
}

bool Device::getIsOnline() const { 
    return isOnline; 
}

void Device::setIsOnline(bool isOnline) { 
    this->isOnline = isOnline; 
}

double Device::getPowerUsage() const { 
    return powerUsage; 
}

void Device::setPowerUsage(double powerUsage) { 
    this->powerUsage = powerUsage; 
}

bool Device::getState() const { 
    return state; 
}

void Device::setState(bool state) { 
    this->state = state; 
}

void Device::log(const std::string &msg) const {
    std::cout << "[ЛОГ][" << name << "] " << msg << std::endl;
}

void Device::registerCallback(DeviceCallback cb) {
    callbacks.push_back(cb);
}
void Device::unregisterCallbacks() {
    callbacks.clear();
}


template<typename T>
requires std::is_arithmetic_v<T>
void Device::scalePower(T factor) {
    powerUsage *= static_cast<double>(factor);
}
