#pragma once
#include "common.hpp"
class Scenario;

class Action {
public:
    Action(const std::string &name = "");
    Action(const Action& other);
    virtual ~Action();
    virtual void execute();
    virtual void scheduleAt(std::time_t at);
    virtual void repeat(std::time_t intervalSeconds, int times);
    virtual void linkWithScenario(std::shared_ptr<Scenario> s);

    std::string getName() const;

private:
    std::string name;
    bool isCompleted;
    bool isCancelled;
    std::time_t scheduledAt;
    std::time_t repeatInterval;
    int repeatTimes;
};
