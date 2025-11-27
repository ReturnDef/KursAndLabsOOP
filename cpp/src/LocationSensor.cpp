#include "../include/LocationSensor.hpp"
#include <cstdio>

LocationSensor::LocationSensor(const std::string &loc): currentLocation(loc) {}

LocationSensor::LocationSensor(const LocationSensor& other): currentLocation(other.currentLocation) {}

void LocationSensor::updateLocation(const std::string &loc) {
    currentLocation = loc;
    std::printf("LocationSensor: местоположение обновлено на %s\n", loc.c_str());
}

std::string LocationSensor::getCurrentLocation() const {
    return currentLocation;
}
