#include <functional>
#pragma once
#include "common.hpp"
#include "Event.hpp"
#include "Scenario.hpp"

class EventRouter {
public:
    using Delegate = std::function<void(const std::string&)>;
    void registerDelegate(Delegate d);
    void unregisterAllDelegates();

    EventRouter() = default;

    void registerEvent(const std::string& type, std::shared_ptr<Event> ev);
    void registerScenarioForEvent(const std::string& eventType, std::shared_ptr<Scenario> s);

    void routeEvent(const std::string& eventType);

private:
    std::vector<Delegate> delegates;

    std::map<std::string, std::vector<std::shared_ptr<Event>>> events;
    std::map<std::string, std::vector<std::shared_ptr<Scenario>>> bindings;
};
