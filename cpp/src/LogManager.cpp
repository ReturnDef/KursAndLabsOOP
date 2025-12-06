#include "LogManager.hpp"
#include <iostream>

void LogManager::add(const std::string& msg) {
    logs.push_back(msg);
}

void LogManager::show() const {
    std::cout << "\n--- Журнал событий ---\n";
    if (logs.empty()) {
        std::cout << "(пусто)\n";
        return;
    }

    for (const auto& l : logs) {
        std::cout << l << "\n";
    }
}

void LogManager::clear() {
    logs.clear();
}

bool LogManager::empty() const {
    return logs.empty();
}

const std::vector<std::string>& LogManager::getLogs() const {
    return logs;
}
