#include "../include/Scheduler.hpp"
#include <cstdio>
#include <algorithm>

void Scheduler::addTask(Action* a) {
    if (a) {
        tasks.push_back(a);
        std::printf("Добавлено задание: %s\n", a->getName().c_str());
    }
}

void Scheduler::removeTask(Action* a) {
    tasks.erase(std::remove(tasks.begin(), tasks.end(), a), tasks.end());
    std::printf("Удалено задание: %s\n", a ? a->getName().c_str() : "(null)");
}

void Scheduler::runPending() {
    std::printf("Выполнение запланированных задач (демо)\n");
    for (auto a: tasks) if (a) a->execute();
}
