#include "SmokeDetector.hpp"

SmokeDetector::SmokeDetector(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), smokeLevel(0.0) {}

SmokeDetector::SmokeDetector(const SmokeDetector& other)
    : Device(other), smokeLevel(other.smokeLevel) {}

SmokeDetector::~SmokeDetector() {}

void SmokeDetector::detectSmoke(double level) {
    smokeLevel = level;
    std::cout << "Датчик дыма '" << getName() << "' уровень=" << smokeLevel << std::endl;
    if (smokeLevel > 5.0) sendAlert();
}

void SmokeDetector::sendAlert() {
    std::cout << "Датчик дыма '" << getName() << "' - ОПАСНОСТЬ: обнаружен дым!" << std::endl;
}

void SmokeDetector::showStatus() {
    std::cout << "Датчик дыма '" << getName() << "' уровень дыма=" << smokeLevel << std::endl;
}