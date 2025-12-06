#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include <vector>
#include "SmartHomeSystem.hpp"
#include "User.hpp"
#include "EnergyMeter.hpp"
#include "Notification.hpp"
#include "Scenario.hpp"

static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readInt() {
    int x;
    while (!(std::cin >> x)) {
        clearInput();
        std::cout << "Неверный ввод, введите число: ";
    }
    clearInput();
    return x;
}

static std::string readLinePrompt(const std::string &prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    if (s.size() == 0) std::getline(std::cin, s);
    return s;
}

void usersMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Пользователи ---\n";
        std::cout << "1. Создать пользователя\n2. Удалить пользователя\n3. Просмотреть всех пользователей\n4. Настройки пользователя\n0. Назад\nВыбор: ";
        int c = readInt();
        if (c == 0) break;
        if (c == 1) {
            int id; std::cout << "id: "; id = readInt();
            std::string name = readLinePrompt("Имя: ");
            auto u = std::make_shared<User>(id, name);
            sys.addUser(u);
        } else if (c == 2) {
            int id; std::cout << "id пользователя для удаления: "; id = readInt();
            sys.removeUser(id);
        } else if (c == 3) {
            auto users = sys.listUsers();
            std::cout << "Список пользователей:\n";
            for (auto &u : users) {
                if (u) std::cout << " - id=" << u->getUserId() << " name='" << u->getName() << "' role='" << u->getRole() << "'\n";
            }
        } else if (c == 4) {
            int id; std::cout << "id пользователя: "; id = readInt();
            auto u = sys.findUser(id);
            if (!u) { std::cout << "Пользователь не найден\n"; continue; }
            while (true) {
                std::cout << "\n--- Настройки пользователя " << u->getName() << " ---\n";
                std::cout << "1. Установить настройку\n2. Получить настройку\n3. Сбросить все настройки\n0. Назад\nВыбор: ";
                int p = readInt();
                if (p == 0) break;
                if (p == 1) {
                    std::string k = readLinePrompt("Ключ: ");
                    std::string v = readLinePrompt("Значение: ");
                    u->setPreference(k, v);
                } else if (p == 2) {
                    std::string k = readLinePrompt("Ключ: ");
                    std::cout << "Значение: " << u->getPreference(k, "<нет>") << "\n";
                } else if (p == 3) {
                    u->resetPreferences();
                }
            }
        } else {
            std::cout << "Неверный выбор\n";
        }
    }
}

void notificationsMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Уведомления ---\n";
        std::cout << "1. Показать все\n2. Очистить (удалить все)\n0. Назад\nВыбор: ";
        int c = readInt();
        if (c == 0) break;
        if (c == 1) {
            sys.showNotifications();
        } else if (c == 2) {
            sys.clearNotifications();
        } else {
            std::cout << "Неверный выбор\n";
        }
    }
}

void devicesMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Устройства ---\n";
        std::cout << "1. Добавить энергосчётчик\n2. Просмотреть все устройства\n3. Обновить показания счётчика\n4. Управлять устройством (вкл/выкл/статус)\n0. Назад\nВыбор: ";
        int c = readInt();
        if (c == 0) break;
        if (c == 1) {
            int id; std::cout << "id: "; id = readInt();
            std::string name = readLinePrompt("Имя счётчика: ");
            std::string location = readLinePrompt("Локация: ");
            auto m = std::make_shared<EnergyMeter>(id, name, location);
            sys.energy().addMeter(m);
            sys.addDevice(m); // also register as device
        } else if (c == 2) {
            auto devs = sys.getDevices();
            std::cout << "Список устройств:\n";
            for (auto &d : devs) {
                if (d) {
                    std::cout << " - id=" << d->getId() << " name='" << d->getName() << "' location='" << d->getLocation() << "'\n";
                }
            }
        } else if (c == 3) {
            int id; std::cout << "id счётчика: "; id = readInt();
            double val; std::cout << "Добавить количество: "; std::cin >> val; clearInput();
            auto dev = sys.findDevice(id);
            if (!dev) { std::cout << "Устройство не найдено\n"; continue; }
            auto em = std::dynamic_pointer_cast<EnergyMeter>(dev);
            if (!em) { std::cout << "Устройство не является энергосчётчиком\n"; continue; }
            em->updateUsage(val);
        } else if (c == 4) {
            int id; std::cout << "id устройства: "; id = readInt();
            auto dev = sys.findDevice(id);
            if (!dev) { std::cout << "Устройство не найдено\n"; continue; }
            std::cout << "1. Включить\n2. Выключить\n3. Статус\nВыбор: ";
            int a = readInt();
            if (a == 1) dev->turnOn();
            else if (a == 2) dev->turnOff();
            else if (a == 3) dev->showStatus();
            else std::cout << "Неверный выбор\n";
        } else {
            std::cout << "Неверный выбор\n";
        }
    }
}

void energyMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Энергопотребление ---\n";
        std::cout << "1. Показать общий расход\n2. Показать расход по всем счётчикам\n0. Назад\nВыбор: ";
        int c = readInt();
        if (c == 0) break;
        if (c == 1) {
            std::cout << "Общий расход: " << sys.getTotalEnergyConsumption() << "\n";
        } else if (c == 2) {
            // List meters by iterating devices and showing EnergyMeter entries
            auto devs = sys.getDevices();
            std::cout << "Расход по счётчикам:\n";
            for (auto &d : devs) {
                auto em = std::dynamic_pointer_cast<EnergyMeter>(d);
                if (em) {
                    std::cout << " - " << em->getName() << " (id=" << em->getId() << "): " << em->getMonthlyReport() << "\n";
                }
            }
        } else {
            std::cout << "Неверный выбор\n";
        }
    }
}

void scenariosMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Сценарии ---\n";
        std::cout << "1. Добавить простой сценарий (только имя)\n2. Список сценариев\n3. Запустить сценарий (по индексу)\n0. Назад\nВыбор: ";
        int c = readInt();
        if (c == 0) break;
        if (c == 1) {
            std::string name = readLinePrompt("Имя сценария: ");
            auto s = std::make_shared<Scenario>(name);
            sys.addScenario(s);
        } else if (c == 2) {
            auto scs = sys.getScenarios();
            std::cout << "Список сценариев:\n";
            for (size_t i = 0; i < scs.size(); ++i) {
                if (scs[i]) std::cout << i << ". " << scs[i]->getName() << "\n";
            }
        } else if (c == 3) {
            auto scs = sys.getScenarios();
            std::cout << "Введите индекс сценария: ";
            int idx = readInt();
            if (idx < 0 || idx >= (int)scs.size()) { std::cout << "Неверный индекс\n"; continue; }
            if (scs[idx]) scs[idx]->execute();
        } else {
            std::cout << "Неверный выбор\n";
        }
    }
}

int main() {
    SmartHomeSystem sys;

    std::cout << "============== SMART HOME CONTROL ==============\n";
    while (true) {
        std::cout << "\nГлавное меню:\n";
        std::cout << "1. Пользователи\n2. Уведомления\n3. Устройства\n4. Энергопотребление\n5. Сценарии\n0. Выход\nВыбор: ";
        int c = readInt();
        if (c == 0) break;
        if (c == 1) usersMenu(sys);
        else if (c == 2) notificationsMenu(sys);
        else if (c == 3) devicesMenu(sys);
        else if (c == 4) energyMenu(sys);
        else if (c == 5) scenariosMenu(sys);
        else std::cout << "Неверный выбор\n";
    }

    std::cout << "Выход. До свидания.\n";
    return 0;
}
