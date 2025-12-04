#pragma once
#include "common.hpp"

class LocationSensor {
public:
    LocationSensor(const std::string &loc = "");
    LocationSensor(const LocationSensor& other);
    void updateLocation(const std::string &loc);
    std::string getCurrentLocation() const;

private:
    std::string currentLocation;
};
