#include "LocationSensor.hpp"

LocationSensor::LocationSensor(const std::string &loc): currentLocation(loc) {}

LocationSensor::LocationSensor(const LocationSensor& other): currentLocation(other.currentLocation) {}

void LocationSensor::updateLocation(const std::string &loc) {
    currentLocation = loc;
    std::cout << "Датчик местоположения: местоположение обновлено на " << loc << std::endl;
}

std::string LocationSensor::getCurrentLocation() const {
    return currentLocation;
}