#pragma once
#include <vector>

class TemperatureHistory {
private:
    std::vector<double> hist;

public:
    TemperatureHistory();

    void add(double t);
    void addTemperature(double t);

    void show() const;
    void clear();

    // Методы, которые реализованы в .cpp — обязательно объявить!
    double getLast() const;
    double average() const;
    double min() const;
    double max() const;
    size_t size() const;
};
