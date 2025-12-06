#include "Action.hpp"

Action::Action(const std::string &name)
    : name(name), isCompleted(false), isCancelled(false),
      scheduledAt(0), repeatInterval(0), repeatTimes(0) {}

Action::Action(const Action& other)
    : name(other.name), isCompleted(other.isCompleted), isCancelled(other.isCancelled),
      scheduledAt(other.scheduledAt), repeatInterval(other.repeatInterval), repeatTimes(other.repeatTimes) {}

Action::~Action() {}

void Action::scheduleAt(std::time_t at) {
    scheduledAt = at;
    std::cout << "[Действие] " << name << " запланировано на " << at << std::endl;
}

void Action::repeat(std::time_t intervalSeconds, int times) {
    repeatInterval = intervalSeconds;
    repeatTimes = times;
    std::cout << "[Действие] " << name << " повтор каждые " << intervalSeconds << " секунд, количество: " << times << std::endl;
}

void Action::linkWithScenario(std::shared_ptr<Scenario> /*s*/) {
    std::cout << "[Действие] " << name << " связано со сценарием (демо)" << std::endl;
}

std::string Action::getName() const { 
    return name; 
}