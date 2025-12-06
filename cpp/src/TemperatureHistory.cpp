#include "TemperatureHistory.hpp"
#include <iostream>
#include <limits>
#include <numeric>

TemperatureHistory::TemperatureHistory() {}

void TemperatureHistory::add(double t) {
    hist.push_back(t);
}

void TemperatureHistory::addTemperature(double t) {
    add(t);
}

void TemperatureHistory::show() const {
    std::cout << "\n--- История температур ---\n";
    if (hist.empty()) {
        std::cout << "(нет данных)\n";
        return;
    }

    for (auto x : hist)
        std::cout << x << " ";

    std::cout << "\n";
}

void TemperatureHistory::clear() {
    hist.clear();
}

double TemperatureHistory::getLast() const {
    if (hist.empty()) return std::numeric_limits<double>::quiet_NaN();
    return hist.back();
}

double TemperatureHistory::average() const {
    if (hist.empty()) return 0.0;
    double sum = std::accumulate(hist.begin(), hist.end(), 0.0);
    return sum / hist.size();
}

double TemperatureHistory::min() const {
    if (hist.empty()) return std::numeric_limits<double>::quiet_NaN();
    return *std::min_element(hist.begin(), hist.end());
}

double TemperatureHistory::max() const {
    if (hist.empty()) return std::numeric_limits<double>::quiet_NaN();
    return *std::max_element(hist.begin(), hist.end());
}

size_t TemperatureHistory::size() const {
    return hist.size();
}
