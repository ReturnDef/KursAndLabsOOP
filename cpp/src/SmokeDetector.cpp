#include "../include/SmokeDetector.hpp"
#include <cstdio>

SmokeDetector::SmokeDetector(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), smokeLevel(0.0) {}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::detectSmoke(double level) {
    smokeLevel = level;
    std::printf("SmokeDetector::detectSmoke для '%s' level=%.2f\n", getName().c_str(), smokeLevel);
    if (smokeLevel > 5.0) sendAlert();
}

void SmokeDetector::sendAlert() {
    std::printf("SmokeDetector::sendAlert для '%s' - ОПАСНО: зафиксирован дым!\n", getName().c_str());
}

void SmokeDetector::showStatus() {
    std::printf("SmokeDetector '%s' smoke=%.2f\n", getName().c_str(), smokeLevel);
}
