#pragma once
#include "common.hpp"
#include "Action.hpp"

class Scheduler {
public:
    void addTask(Action* a);
    void removeTask(Action* a);
    void runPending();

private:
    std::vector<Action*> tasks;
};
