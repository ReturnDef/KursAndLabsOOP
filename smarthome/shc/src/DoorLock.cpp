#include "DoorLock.hpp"

DoorLock::DoorLock(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), isLocked(true) {
    std::cout << "Дверной замок '" << getName() << "' инициализирован (id=" << getId() << ")" << std::endl;
}

DoorLock::DoorLock(const DoorLock& other)
    : Device(other), isLocked(other.isLocked) {}

DoorLock::~DoorLock() {}

void DoorLock::lock() {
    isLocked = true;
    std::cout << "Дверной замок '" << getName() << "' заблокирован" << std::endl;
}

void DoorLock::unlock() {
    isLocked = false;
    std::cout << "Дверной замок '" << getName() << "' разблокирован" << std::endl;
}

void DoorLock::alertIfForced() {
    std::cout << "Проверка взлома для '" << getName() << "' (демо)" << std::endl;
}

void DoorLock::showStatus() {
    std::cout << "Дверной замок '" << getName() << "' заблокирован: " << (isLocked ? "ДА" : "НЕТ") << std::endl;
}