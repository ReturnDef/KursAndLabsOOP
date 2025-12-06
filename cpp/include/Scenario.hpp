#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Action.hpp"

class Scenario {
public:
    Scenario(const std::string& name);

    void addAction(std::shared_ptr<Action> act);

    // Старый интерфейс для совместимости
    void execute();             // просто вызывает run()
    void run();                 // реальное выполнение

    void showActions() const;

    // ID — потому что SmartHomeSystem ожидает эти методы
    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    const std::string& getName() const { return name; }

private:
    int id = -1;   // Авто-ID
    std::string name;
    std::vector<std::shared_ptr<Action>> actions;
};
