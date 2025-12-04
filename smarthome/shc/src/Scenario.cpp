#include "Scenario.hpp"

Scenario::Scenario(const std::string &name): name(name), isActive(false) {}

Scenario::Scenario(const Scenario& other)
    : name(other.name), actions(other.actions), triggers(other.triggers), isActive(other.isActive) {}

void Scenario::addAction(std::shared_ptr<Action> a) {
    if (a) {
        actions.push_back(a);
        std::cout << "Добавлено действие '" << a->getName() << "' в сценарий '" << name << "'" << std::endl;
    }
}

void Scenario::addTrigger(std::shared_ptr<Event> e) {
    if (e) {
        triggers.push_back(e);
        std::cout << "Добавлен триггер '" << e->getInfo() << "' в сценарий '" << name << "'" << std::endl;
    }
}

void Scenario::execute() {
    std::cout << "Выполнение сценария: " << name << std::endl;
    for (auto a: actions) if (a) a->execute();
    isActive = true;
}

std::string Scenario::getName() const { 
    return name; 
}

std::shared_ptr<Scenario> Scenario::cloneShallow() const {
    return std::make_shared<Scenario>(*this);
}

std::shared_ptr<Scenario> Scenario::cloneDeep() const {
    auto s = std::make_shared<Scenario>(name);
    for (auto &a : actions) {
        if (a) s->addAction(a->clone());
    }
    for (auto &e : triggers) {
        if (e) s->addTrigger(std::make_shared<Event>(*e));
    }
    s->isActive = isActive;
    return s;
}

void Scenario::adaptTo(const std::string &newName) {
    for (auto &a : actions) if (a) a->modifyForScenario(newName);
    name = newName;
}