#include "Scheduler.hpp"

Scheduler::Scheduler() {}

void Scheduler::addTask(std::shared_ptr<Action> a) {
    if (a) {
        tasks.push_back(a);
        std::cout << "Добавлена задача: " << a->getName() << std::endl;
    }
}

void Scheduler::removeTask(std::shared_ptr<Action> a) {
    tasks.erase(std::remove(tasks.begin(), tasks.end(), a), tasks.end());
    std::cout << "Задача удалена" << std::endl;
}

void Scheduler::runPending() {
    std::cout << "Запуск запланированных задач (демо)" << std::endl;
    for (auto a: tasks) if (a) a->execute();
}