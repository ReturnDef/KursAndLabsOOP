#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Action.hpp"
#include "Notification.hpp"
#include "NotificationCenter.hpp"

enum class ScenarioStatus { Idle, Running, Completed, Failed };

class Scenario {
public:
    Scenario(const std::string& name);
    Scenario(const std::string& name, const std::string& description);

    ScenarioStatus getStatus() const { return status; }

    const std::string& getDescription() const { return description; }

    void setNotifier(std::function<void(const Notification&)> cb) { notifier = cb; }

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
    ScenarioStatus status = ScenarioStatus::Idle;
    std::function<void(const Notification&)> notifier;
    std::string description;
    std::vector<std::shared_ptr<Action>> actions;
};
