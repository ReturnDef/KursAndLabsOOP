#include "Sprinkler.hpp"

Sprinkler::Sprinkler(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), flowRate(0.0) {}

Sprinkler::Sprinkler(const Sprinkler& other)
    : Device(other), flowRate(other.flowRate) {}

Sprinkler::~Sprinkler() {}

void Sprinkler::turnOnSprinkler() {
    std::cout << "Спринклер '" << getName() << "' включен" << std::endl;
}

void Sprinkler::turnOffSprinkler() {
    std::cout << "Спринклер '" << getName() << "' выключен" << std::endl;
}

void Sprinkler::scheduleWatering(std::time_t when) {
    std::cout << "Спринклер '" << getName() << "' запланирован полив на " << when << " (демо)" << std::endl;
}

void Sprinkler::showStatus() {
    std::cout << "Спринклер '" << getName() << "' поток: " << flowRate << std::endl;
}