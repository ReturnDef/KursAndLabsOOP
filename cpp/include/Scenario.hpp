#pragma once
#include "common.hpp"
#include "Action.hpp"
#include "Event.hpp"

class Scenario {
public:
    Scenario(const std::string &name = "");
    void addAction(Action* a);
    void addTrigger(Event* e);
    void execute();

    std::string getName() const;

private:
    std::string name;
    std::vector<Action*> actions;
    std::vector<Event*> triggers;
    bool isActive;
};
