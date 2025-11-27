#pragma once
#include "common.hpp"
#include "Action.hpp"

class Scheduler {
public:
    void addTask(std::shared_ptr<Action> a);
    void removeTask(std::shared_ptr<Action> a);
    void runPending();

private:
    std::vector<std::shared_ptr<Action>> tasks;
};
