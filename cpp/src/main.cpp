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
#include "LogManager.hpp"
#include "TemperatureHistory.hpp"
#include "Light.hpp"
#include "Heater.hpp"
#include "Thermostat.hpp"
#include "WindowBlind.hpp"
#include "Sprinkler.hpp"
#include "DoorLock.hpp"
#include "SmokeDetector.hpp"


// ==================== Вспомогательные функции ====================

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
    if (s.empty()) std::getline(std::cin, s);
    return s;
}

// ====================== Меню пользователей ======================

void usersMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Пользователи ---\n";
        std::cout << "1. Создать пользователя\n";
        std::cout << "2. Удалить пользователя\n";
        std::cout << "3. Просмотреть всех пользователей\n";
        std::cout << "4. Настройки пользователя\n";
        std::cout << "0. Назад\n";
        std::cout << "Выбор: ";

        int c = readInt();
        if (c == 0) break;

        if (c == 1) {
            int id = readInt();
            std::string name = readLinePrompt("Имя: ");
            sys.addUser(std::make_shared<User>(id, name));

        } else if (c == 2) {
            int id = readInt();
            sys.removeUser(id);

        } else if (c == 3) {
            auto users = sys.listUsers();
            std::cout << "Список пользователей:\n";
            for (auto &u : users) {
                if (u) {
                    std::cout << " - id=" << u->getUserId()
                              << " name='" << u->getName()
                              << "' role='" << u->getRole() << "'\n";
                }
            }

        } else if (c == 4) {
            int id = readInt();
            auto u = sys.findUser(id);
            if (!u) {
                std::cout << "Пользователь не найден\n";
                continue;
            }

            while (true) {
                std::cout << "\n--- Настройки пользователя " << u->getName() << " ---\n";
                std::cout << "1. Установить настройку\n";
                std::cout << "2. Получить настройку\n";
                std::cout << "3. Сбросить все настройки\n";
                std::cout << "0. Назад\nВыбор: ";

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
        }
    }
}

// ====================== Меню уведомлений ======================

void notificationsMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Уведомления ---\n";
        std::cout << "1. Показать все\n";
        std::cout << "2. Очистить все\n";
        std::cout << "0. Назад\nВыбор: ";

        int c = readInt();
        if (c == 0) break;

        if (c == 1) sys.showNotifications();
        else if (c == 2) sys.clearNotifications();
    }
}

// ====================== Меню устройств ======================

void devicesMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Устройства ---\n";
        std::cout << "1. Добавить устройство\n";
        std::cout << "2. Просмотреть все устройства\n";
        std::cout << "3. Добавить показания счётчика\n";
        std::cout << "4. Управлять устройством\n";
        std::cout << "0. Назад\nВыбор: ";

        int c = readInt();
        if (c == 0) break;

        if (c == 1) {
            std::cout << "Выберите тип устройства:\n";
            std::cout << "1. Light\n2. Heater\n3. Thermostat\n4. WindowBlind\n5. Sprinkler\n6. DoorLock\n7. SmokeDetector\n8. EnergyMeter\n0. Отмена\nВыбор: ";

            int t = readInt();
            if (t == 0) continue;

            int id = readInt();
            std::string name = readLinePrompt("Имя: ");
            std::string location = readLinePrompt("Локация: ");

            std::shared_ptr<Device> d;

            switch (t) {
                case 1: d = std::make_shared<Light>(id, name, location); break;
                case 2: d = std::make_shared<Heater>(id, name, location); break;
                case 3: d = std::make_shared<Thermostat>(id, name, location); break;
                case 4: d = std::make_shared<WindowBlind>(id, name, location); break;
                case 5: d = std::make_shared<Sprinkler>(id, name, location); break;
                case 6: d = std::make_shared<DoorLock>(id, name, location); break;
                case 7: d = std::make_shared<SmokeDetector>(id, name, location); break;
                case 8: {
                    auto m = std::make_shared<EnergyMeter>(id, name, location);
                    sys.energy().addMeter(m);
                    d = m;
                } break;
                default:
                    std::cout << "Неверный тип\n";
                    continue;
            }

            sys.addDevice(d);
            std::cout << "Устройство добавлено.\n";

        } else if (c == 2) {
            auto devs = sys.getDevices();
            std::cout << "Список устройств:\n";
            for (auto &d : devs) {
                if (d) {
                    std::cout << " - id=" << d->getId()
                              << " name='" << d->getName()
                              << "' location='" << d->getLocation() << "'\n";
                }
            }

        } else if (c == 3) {
            int id;
            std::cout << "id счётчика: ";
            id = readInt();

            double val;
            std::cout << "Количество: ";
            std::cin >> val;
            clearInput();

            auto dev = sys.findDevice(id);
            if (!dev) {
                std::cout << "Устройство не найдено\n";
                continue;
            }

            auto em = std::dynamic_pointer_cast<EnergyMeter>(dev);
            if (!em) {
                std::cout << "Это не энергосчётчик\n";
                continue;
            }

            em->updateUsage(val);
            std::cout << "Показания добавлены.\n";

        } else if (c == 4) {
            int id = readInt();
            auto dev = sys.findDevice(id);

            if (!dev) {
                std::cout << "Устройство не найдено\n";
                continue;
            }

            std::cout << "1. Включить\n2. Выключить\n3. Статус\nВыбор: ";
            int a = readInt();

            if (a == 1) dev->turnOn();
            else if (a == 2) dev->turnOff();
            else if (a == 3) dev->showStatus();
        }
    }
}

// ====================== Меню энергии ======================

void energyMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Энергопотребление ---\n";
        std::cout << "1. Общий расход\n";
        std::cout << "2. По счётчикам\n";
        std::cout << "0. Назад\nВыбор: ";

        int c = readInt();
        if (c == 0) break;

        if (c == 1) {
            std::cout << "Общий расход: " << sys.getTotalEnergyConsumption() << "\n";

        } else if (c == 2) {
            std::cout << "Расход по счётчикам:\n";
            for (auto &d : sys.getDevices()) {
                auto em = std::dynamic_pointer_cast<EnergyMeter>(d);
                if (em) {
                    std::cout << " - " << em->getName()
                              << " (id=" << em->getId()
                              << "): " << em->getMonthlyReport() << "\n";
                }
            }
        }
    }
}

// ====================== Меню сценариев ======================

void scenariosMenu(SmartHomeSystem &sys) {
    while (true) {
        std::cout << "\n--- Сценарии ---\n";
        std::cout << "1. Добавить сценарий\n";
        std::cout << "2. Список сценариев\n";
        std::cout << "3. Запустить\n";
        std::cout << "0. Назад\nВыбор: ";

        int c = readInt();
        if (c == 0) break;

        if (c == 1) {
            std::string name = readLinePrompt("Имя: ");
            sys.addScenario(std::make_shared<Scenario>(name));

        } else if (c == 2) {
            auto scs = sys.getScenarios();
            for (size_t i = 0; i < scs.size(); ++i)
                std::cout << i << ". " << scs[i]->getName() << "\n";

        } else if (c == 3) {
            int idx = readInt();
            auto scs = sys.getScenarios();

            if (idx < 0 || idx >= (int)scs.size()) {
                std::cout << "Неверный индекс\n";
                continue;
            }

            scs[idx]->execute();
        }
    }
}

// ====================== Журнал событий ======================

void logMenu(LogManager &log) {
    while (true) {
        std::cout << "\n--- Журнал событий ---\n";
        std::cout << "1. Показать журнал\n";
        std::cout << "2. Очистить журнал\n";
        std::cout << "0. Назад\nВыбор: ";

        int c = readInt();
        if (c == 0) break;

        if (c == 1) log.show();
        else if (c == 2) log.clear();
    }
}

// ====================== История температур ======================

void tempHistoryMenu(TemperatureHistory &hist) {
    while (true) {
        std::cout << "\n--- История температур ---\n";
        std::cout << "1. Добавить запись\n";
        std::cout << "2. Просмотреть историю\n";
        std::cout << "0. Назад\nВыбор: ";

        int c = readInt();
        if (c == 0) break;

        if (c == 1) {
            double t;
            std::cout << "Температура: ";
            std::cin >> t;
            clearInput();
            hist.addTemperature(t);

        } else if (c == 2) hist.show();
    }
}

// ============================ MAIN ============================

int main() {
    SmartHomeSystem sys;
    LogManager log;
    TemperatureHistory tempHistory;

    std::cout << "============== SMART HOME CONTROL ==============\n";

    while (true) {
        std::cout << "\nГлавное меню:\n";
        std::cout << "1. Устройства\n";
        std::cout << "2. Сценарии\n";
        std::cout << "3. Уведомления\n";
        std::cout << "4. Энергопотребление\n";
        std::cout << "5. Пользователи\n";
        std::cout << "7. Журнал событий\n";
        std::cout << "8. История температур\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";

        int c = readInt();
        if (c == 0) break;

        if      (c == 1) devicesMenu(sys);
        else if (c == 2) scenariosMenu(sys);
        else if (c == 3) notificationsMenu(sys);
        else if (c == 4) energyMenu(sys);
        else if (c == 5) usersMenu(sys);
        else if (c == 7) logMenu(log);
        else if (c == 8) tempHistoryMenu(tempHistory);
        else std::cout << "Неверный выбор\n";
    }

    std::cout << "Выход. До свидания.\n";
    return 0;
}
