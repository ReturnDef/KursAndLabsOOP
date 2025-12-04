#pragma once
#include "common.hpp"
class Scenario;

class Action {
public:
    Action(const std::string &name = "");
    Action(const Action& other);
    virtual ~Action();

    virtual void execute() = 0;

    virtual void scheduleAt(std::time_t at);
    virtual void repeat(std::time_t intervalSeconds, int times);
    virtual void linkWithScenario(std::shared_ptr<Scenario> s);

    std::string getName() const;

    virtual std::shared_ptr<Action> clone() const = 0;

    virtual void modifyForScenario(const std::string &scenarioName) = 0;

protected:
    std::string name;
    bool isCompleted;
    bool isCancelled;
    std::time_t scheduledAt;
    std::time_t repeatInterval;
    int repeatTimes;
};