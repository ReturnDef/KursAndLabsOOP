#pragma once
#include "common.hpp"
#include "Action.hpp"

class Event {
public:
    Event(const std::string &desc = "");
    void trigger();
    std::string getInfo() const;
    void linkActions(const std::vector<Action*>& act);

private:
    std::string description;
    std::vector<Action*> actions;
};
