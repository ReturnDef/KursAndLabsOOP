#include <functional>
#include "EventRouter.hpp"

void EventRouter::registerEvent(const std::string& type, std::shared_ptr<Event> ev) {
    events[type].push_back(ev);
}

void EventRouter::registerScenarioForEvent(const std::string& eventType, std::shared_ptr<Scenario> s) {
    bindings[eventType].push_back(s);
}

void EventRouter::routeEvent(const std::string& eventType) {
    // Delegate callbacks
    for (auto &d : delegates) if (d) d(eventType);

    std::cout << "Маршрутизация события типа: " << eventType << std::endl;
    auto it = bindings.find(eventType);
    if (it != bindings.end()) {
        for (auto &sc : it->second) if (sc) sc->execute();
    }
    auto evIt = events.find(eventType);
    if (evIt != events.end()) {
        for (auto &e : evIt->second) if (e) e->trigger();
    }
}
void EventRouter::registerDelegate(Delegate d) { delegates.push_back(d); }
void EventRouter::unregisterAllDelegates() { delegates.clear(); }
