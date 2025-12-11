#include "Scenario.hpp"
#include "DeviceAction.hpp"
#include "NotificationCenter.hpp"
#include <iostream>

Scenario::Scenario(const std::string& name)
    : name(name), description("") {}

Scenario::Scenario(const std::string& name, const std::string& description)
    : name(name), description(description) {}

void Scenario::addAction(std::shared_ptr<Action> act) {
    actions.push_back(act);
}

void Scenario::execute() {
    run();
}

void Scenario::run() {
    std::cout << "\n=== Запуск сценария: " << name << " (ID=" << id << ") ===\n";
    if (!description.empty())
        std::cout << description << "\n";

    std::cout << "------------------------------------\n";

    status = ScenarioStatus::Running;

    Notification startN("Сценарий начат: " + name);
    NotificationCenter::instance().notify(startN);

    for (size_t i = 0; i < actions.size(); ++i) {
        auto& act = actions[i];
        std::cout << "→ Шаг " << (i + 1) << ": " << act->getDescription() << "\n";
        act->execute();
    }

    std::cout << "------------------------------------\n";
    std::cout << "=== Сценарий '" << name << "' завершён ===\n\n";

    status = ScenarioStatus::Completed;

    Notification finishN("Сценарий выполнен: " + name);
    NotificationCenter::instance().notify(finishN);
}

void Scenario::showActions() const {
    std::cout << "\n--- Действия сценария '" << name << "' (ID=" << id << ") ---\n";

    for (const auto& a : actions) {
        std::cout << "* " << a->getName();
        if (std::dynamic_pointer_cast<DeviceAction>(a))
            std::cout << " (действие с устройством)";
        std::cout << "\n";
    }
}
