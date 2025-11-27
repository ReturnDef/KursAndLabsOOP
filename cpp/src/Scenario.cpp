#include "../include/Scenario.hpp"
#include <cstdio>

Scenario::Scenario(const std::string &name): name(name), isActive(false) {}

Scenario::Scenario(const Scenario& other)
    : name(other.name), actions(other.actions), triggers(other.triggers), isActive(other.isActive) {}

void Scenario::addAction(std::shared_ptr<Action> a) {
    if (a) {
        actions.push_back(a);
        std::printf("Добавлено действие '%s' в сценарий '%s'\n", a->getName().c_str(), name.c_str());
    }
}

void Scenario::addTrigger(std::shared_ptr<Event> e) {
    if (e) {
        triggers.push_back(e);
        std::printf("Добавлен триггер '%s' в сценарий '%s'\n", e->getInfo().c_str(), name.c_str());
    }
}

void Scenario::execute() {
    std::printf("Выполнение сценария: %s\n", name.c_str());
    for (auto a: actions) if (a) a->execute();
    isActive = true;
}

std::string Scenario::getName() const {
    return name;
}
