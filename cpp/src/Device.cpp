#include "../include/Device.hpp"
#include <cstdio>

Device::Device(int id, const std::string &name, const std::string &location)
    : id(id), name(name), location(location), isOnline(true), powerUsage(0.0), state(false) {}

Device::Device(const Device& other)
    : id(other.id), name(other.name), location(other.location), isOnline(other.isOnline), powerUsage(other.powerUsage), state(other.state) {}

Device::~Device() {}

void Device::turnOn() {
    state = true;
    std::printf("Устройство '%s' включено\n", name.c_str());
}

void Device::turnOff() {
    state = false;
    std::printf("Устройство '%s' выключено\n", name.c_str());
}

void Device::showStatus() {
    std::printf("Статус устройства '%s': %s, местоположение: %s\n", name.c_str(), state ? "ВКЛ" : "ВЫКЛ", location.c_str());
}

void Device::performAction(std::shared_ptr<Action>) {
    std::printf("Устройство '%s' выполняет базовое действие\n", name.c_str());
}

double Device::getEnergyUsage() const {
    return powerUsage;
}

void Device::updateFirmware() {
    std::printf("Обновление прошивки для '%s' (демо)\n", name.c_str());
}

int Device::getId() const { return id; }
void Device::setId(int id) { this->id = id; }

std::string Device::getName() const { return name; }
void Device::setName(const std::string &name) { this->name = name; }

std::string Device::getLocation() const { return location; }
void Device::setLocation(const std::string &location) { this->location = location; }

bool Device::getIsOnline() const { return isOnline; }
void Device::setIsOnline(bool isOnline) { this->isOnline = isOnline; }

double Device::getPowerUsage() const { return powerUsage; }
void Device::setPowerUsage(double powerUsage) { this->powerUsage = powerUsage; }

bool Device::getState() const { return state; }
void Device::setState(bool state) { this->state = state; }
