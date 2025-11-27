#include "../include/Action.hpp"
#include <cstdio>

Action::Action(const std::string &name): name(name), isCompleted(false), isCancelled(false), scheduledAt(0), repeatInterval(0), repeatTimes(0) {}
Action::Action(const Action& other)
    : name(other.name), isCompleted(other.isCompleted), isCancelled(other.isCancelled), scheduledAt(other.scheduledAt), repeatInterval(other.repeatInterval), repeatTimes(other.repeatTimes) {}
Action::~Action() {}

void Action::execute() {
    std::printf("Выполнение действия: %s\n", name.c_str());
    isCompleted = true;
}

void Action::scheduleAt(std::time_t at) {
    scheduledAt = at;
    std::printf("Действие '%s' запланировано на %ld\n", name.c_str(), (long)at);
}

void Action::repeat(std::time_t intervalSeconds, int times) {
    repeatInterval = intervalSeconds;
    repeatTimes = times;
    std::printf("Действие '%s' будет повторяться %d раз каждые %ld секунд (демо)\n", name.c_str(), times, (long)intervalSeconds);
}

void Action::linkWithScenario(std::shared_ptr<Scenario>) {
    std::printf("Действие '%s' связано со сценарием (демо)\n", name.c_str());
}

std::string Action::getName() const {
    return name;
}
