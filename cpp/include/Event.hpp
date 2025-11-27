#pragma once
#include "common.hpp"
#include "Action.hpp"

class Event {
public:
    Event(const std::string &desc = "");
    Event(const Event& other);
    void trigger();
    std::string getInfo() const;
    void linkActions(const std::vector<std::shared_ptr<Action>>& act);

private:
    std::string description;
    std::vector<std::shared_ptr<Action>> actions;
};
