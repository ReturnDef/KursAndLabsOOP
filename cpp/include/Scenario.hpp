#pragma once
#include "common.hpp"
#include "Action.hpp"
#include "Event.hpp"

class Scenario {
public:
    Scenario(const std::string &name = "");
    Scenario(const Scenario& other);
    void addAction(std::shared_ptr<Action> a);
    void addTrigger(std::shared_ptr<Event> e);
    void execute();

    std::string getName() const;

private:
    std::string name;
    std::vector<std::shared_ptr<Action>> actions;
    std::vector<std::shared_ptr<Event>> triggers;
    bool isActive;
};
