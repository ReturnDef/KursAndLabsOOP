#include "../include/Event.hpp"
#include <cstdio>

Event::Event(const std::string &desc): description(desc) {}
Event::Event(const Event& other): description(other.description), actions(other.actions) {}

void Event::trigger() {
    std::printf("Событие triggered: %s\n", description.c_str());
    for (auto a: actions) if (a) a->execute();
}

std::string Event::getInfo() const {
    return description;
}

void Event::linkActions(const std::vector<std::shared_ptr<Action>>& act) {
    actions = act;
    std::printf("Действия связаны с событием '%s' (кол-во: %zu)\n", description.c_str(), actions.size());
}
