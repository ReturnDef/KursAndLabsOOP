#include "../include/DoorLock.hpp"
#include <cstdio>

DoorLock::DoorLock(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), isLocked(true) {}

DoorLock::~DoorLock() {}

void DoorLock::lock() {
    isLocked = true;
    std::printf("DoorLock::lock вызван для '%s'\n", getName().c_str());
}

void DoorLock::unlock() {
    isLocked = false;
    std::printf("DoorLock::unlock вызван для '%s'\n", getName().c_str());
}

void DoorLock::alertIfForced() {
    std::printf("DoorLock::alertIfForced для '%s' (демо)\n", getName().c_str());
}

void DoorLock::showStatus() {
    std::printf("DoorLock '%s' locked: %s\n", getName().c_str(), isLocked ? "ДА" : "НЕТ");
}
