#include "Event.hpp"

Event::Event(const std::string &desc): description(desc) {}
Event::Event(const Event& other): description(other.description), actions(other.actions) {}

void Event::trigger() {
    std::cout << "Событие запущено: " << description << std::endl;
    for (auto a: actions) if (a) a->execute();
}

std::string Event::getInfo() const {
    return description;
}

void Event::linkActions(const std::vector<std::shared_ptr<Action>>& act) {
    actions = act;
    std::cout << "Действия связаны с событием '" << description << "' (количество: " << actions.size() << ")" << std::endl;
}