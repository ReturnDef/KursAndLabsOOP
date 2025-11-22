#include "../include/Event.hpp"
#include <cstdio>

Event::Event(const std::string &desc): description(desc) {}

void Event::trigger() {
    std::printf("Событие triggered: %s\n", description.c_str());
    for (auto a: actions) if (a) a->execute();
}

std::string Event::getInfo() const {
    return description;
}

void Event::linkActions(const std::vector<Action*>& act) {
    actions = act;
    std::printf("Действия связаны с событием '%s' (кол-во: %zu)\n", description.c_str(), actions.size());
}
