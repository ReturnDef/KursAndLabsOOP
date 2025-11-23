#include "../include/Sprinkler.hpp"
#include <cstdio>

Sprinkler::Sprinkler(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), flowRate(0.0) {}

Sprinkler::~Sprinkler() {}

void Sprinkler::turnOnSprinkler() {
    std::printf("Sprinkler::turnOnSprinkler для '%s'\n", getName().c_str());
}

void Sprinkler::turnOffSprinkler() {
    std::printf("Sprinkler::turnOffSprinkler для '%s'\n", getName().c_str());
}

void Sprinkler::scheduleWatering(std::time_t when) {
    std::printf("Sprinkler::scheduleWatering для '%s' на %ld (демо)\n", getName().c_str(), (long)when);
}

void Sprinkler::showStatus() {
    std::printf("Sprinkler '%s' расход: %.2f\n", getName().c_str(), flowRate);
}
