#pragma once
#include <string>
#include <vector>

class LogManager {
private:
    std::vector<std::string> logs;

public:
    void add(const std::string& msg);
    void show() const;
    void clear();
    bool empty() const;
    const std::vector<std::string>& getLogs() const;
};
