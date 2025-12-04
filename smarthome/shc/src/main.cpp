#include <iostream>
#include <memory>
#include <string>
#include "SmartHomeSystem.hpp"
#include "Camera.hpp"
#include "Heater.hpp"
#include "Light.hpp"
#include "WindowBlind.hpp"
#include "SmokeDetector.hpp"
#include "Sprinkler.hpp"
#include "Thermostat.hpp"
#include "EnergyMeter.hpp"
#include "Scenario.hpp"
#include "DeviceAction.hpp"
#include "Event.hpp"
#include "EventRouter.hpp"
#include "User.hpp"

void menuDevices(std::shared_ptr<SmartHomeSystem> sys) {
    while (true) {
        std::cout << "\n=== УСТРОЙСТВА ===" << std::endl;
        std::cout << "1 — Показать устройства" << std::endl;
        std::cout << "2 — Добавить устройство" << std::endl;
        std::cout << "0 — Назад" << std::endl;
        std::cout << "> ";
        int c; 
        std::cin >> c;
        if (c == 0) return;
        if (c == 1) sys->showDevices();
        if (c == 2) {
            std::cout << "Выберите тип:" << std::endl;
            std::cout << "1 — Камера" << std::endl;
            std::cout << "2 — Обогреватель" << std::endl;
            std::cout << "3 — Свет" << std::endl;
            std::cout << "4 — Жалюзи" << std::endl;
            std::cout << "5 — Детектор дыма" << std::endl;
            std::cout << "6 — Спринклер" << std::endl;
            std::cout << "7 — Термостат" << std::endl;
            std::cout << "8 — Энергосчетчик" << std::endl;
            std::cout << "> ";
            int t; 
            std::cin >> t;
            int id; 
            std::string name, loc;
            std::cout << "ID: "; 
            std::cin >> id;
            std::cout << "Имя: "; 
            std::cin >> name;
            std::cout << "Локация: "; 
            std::cin >> loc;
            std::shared_ptr<Device> d = nullptr;
            if (t == 1) d = std::make_shared<Camera>(id, name, loc);
            if (t == 2) d = std::make_shared<Heater>(id, name, loc);
            if (t == 3) d = std::make_shared<Light>(id, name, loc);
            if (t == 4) d = std::make_shared<WindowBlind>(id, name, loc);
            if (t == 5) d = std::make_shared<SmokeDetector>(id, name, loc);
            if (t == 6) d = std::make_shared<Sprinkler>(id, name, loc);
            if (t == 7) d = std::make_shared<Thermostat>(id, name, loc);
            if (t == 8) d = std::make_shared<EnergyMeter>(id, name, loc);
            if (d) sys->addDevice(d);
        }
    }
}

void menuScenarios(std::shared_ptr<SmartHomeSystem> sys) {
    while (true) {
        std::cout << "\n=== СЦЕНАРИИ ===" << std::endl;
        std::cout << "1 — Показать сценарии" << std::endl;
        std::cout << "2 — Создать сценарий" << std::endl;
        std::cout << "3 — Добавить действие DeviceAction" << std::endl;
        std::cout << "4 — Запустить" << std::endl;
        std::cout << "5 — Клонировать (поверхностно)" << std::endl;
        std::cout << "6 — Клонировать (глубоко)" << std::endl;
        std::cout << "0 — Назад" << std::endl;
        std::cout << "> ";
        int c; 
        std::cin >> c;
        if (c == 0) return;
        if (c == 1) sys->showScenarios();
        if (c == 2) {
            std::string name; 
            std::cout << "Имя: "; 
            std::cin >> name;
            sys->addScenario(std::make_shared<Scenario>(name));
        }
        if (c == 3) {
            std::string scen; 
            std::cout << "Сценарий: "; 
            std::cin >> scen;
            auto s = sys->findScenario(scen);
            if (!s) { 
                std::cout << "Нет сценария" << std::endl; 
                continue;
            }
            std::string dev; 
            std::cout << "Устройство: "; 
            std::cin >> dev;
            auto d = sys->findDeviceByName(dev);
            if (!d) { 
                std::cout << "Нет устройства" << std::endl; 
                continue;
            }
            std::string actName; 
            std::cout << "Имя действия: "; 
            std::cin >> actName;
            auto a = std::make_shared<DeviceAction>(actName, d, [](std::shared_ptr<Device> dd) { dd->turnOn(); });
            s->addAction(a);
        }
        if (c == 4) {
            std::string scen; 
            std::cout << "Сценарий: "; 
            std::cin >> scen;
            auto s = sys->findScenario(scen);
            if (s) s->execute();
        }
        if (c == 5 || c == 6) {
            std::string oldn, newn;
            std::cout << "Старое имя: "; 
            std::cin >> oldn;
            std::cout << "Новое имя: "; 
            std::cin >> newn;
            sys->duplicateScenario(oldn, newn, c == 6);
        }
    }
}

void menuUsers(std::shared_ptr<SmartHomeSystem> sys) {
    while (true) {
        std::cout << "\n=== ПОЛЬЗОВАТЕЛИ ===" << std::endl;
        std::cout << "1 — Показать" << std::endl;
        std::cout << "2 — Добавить" << std::endl;
        std::cout << "3 — Выполнить сценарий" << std::endl;
        std::cout << "0 — Назад" << std::endl;
        std::cout << "> ";
        int c;
        std::cin >> c;
        if (c == 0) return;
        if (c == 1) {
        }
        if (c == 2) {
            int id; 
            std::string name; 
            std::cout << "ID: ";
            std::cin >> id; 
            std::cout << "Имя: ";
            std::cin >> name;
            sys->addUser(std::make_shared<User>(id, name));
        }
        if (c == 3) {
            int id; 
            std::string scen;
            std::cout << "ID пользователя: ";
            std::cin >> id;
            auto u = sys->findUser(id);
            if (!u) {
                std::cout << "Нет пользователя" << std::endl;
                continue;
            }
            std::cout << "Сценарий: ";
            std::cin >> scen;
            auto s = sys->findScenario(scen);
            if (s) u->executeScenario(s);
        }
    }
}

void menuEnergy(std::shared_ptr<SmartHomeSystem> sys) {
    while (true) {
        std::cout << "\n=== ЭНЕРГИЯ ===" << std::endl;
        std::cout << "1 — Добавить счётчик" << std::endl;
        std::cout << "2 — Показать отчёт" << std::endl;
        std::cout << "0 — Назад" << std::endl;
        std::cout << "> ";
        int c;
        std::cin >> c;
        if (c == 0) return;
        if (c == 1) {
            int id;
            std::string n, l;
            std::cout << "ID: ";
            std::cin >> id;
            std::cout << "Имя: ";
            std::cin >> n;
            std::cout << "Локация: ";
            std::cin >> l;
            auto em = std::make_shared<EnergyMeter>(id, n, l);
            sys->getEnergyManager().addMeter(em);
            sys->addDevice(em);
        }
        if (c == 2) {
            std::cout << "Общее потребление: " << sys->getEnergyManager().getEnergyReport() << std::endl;
        }
    }
}

void menuNotifications(std::shared_ptr<SmartHomeSystem> sys) {
    while (true) {
        std::cout << "\n=== УВЕДОМЛЕНИЯ ===" << std::endl;
        std::cout << "1 — Показать" << std::endl;
        std::cout << "2 — Всем" << std::endl;
        std::cout << "3 — Устройству" << std::endl;
        std::cout << "0 — Назад" << std::endl;
        std::cout << "> ";
        int c;
        std::cin >> c;
        if (c == 0) return;
        if (c == 1) sys->showNotifications();
        if (c == 2) {
            std::string msg; 
            std::cout << "Сообщение: ";
            std::cin >> msg;
            sys->sendNotificationToAll(msg);
        }
        if (c == 3) {
            int id; 
            std::string msg;
            std::cout << "ID устройства: ";
            std::cin >> id;
            std::cout << "Сообщение: ";
            std::cin >> msg;
            sys->sendNotificationToDevice(id, msg);
        }
    }
}

void menuEvents(std::shared_ptr<EventRouter> r, std::shared_ptr<SmartHomeSystem> sys) {
    while (true) {
        std::cout << "\n=== СОБЫТИЯ ===" << std::endl;
        std::cout << "1 — Зарегистрировать" << std::endl;
        std::cout << "2 — Привязать сценарий" << std::endl;
        std::cout << "3 — Вызвать" << std::endl;
        std::cout << "0 — Назад" << std::endl;
        std::cout << "> ";
        int c;
        std::cin >> c;
        if (c == 0) return;
        if (c == 1) {
            std::string t, d; 
            std::cout << "Тип события: ";
            std::cin >> t; 
            std::cout << "Описание: ";
            std::cin >> d;
            r->registerEvent(t, std::make_shared<Event>(d));
        }
        if (c == 2) {
            std::string t, s; 
            std::cout << "Тип события: ";
            std::cin >> t; 
            std::cout << "Сценарий: ";
            std::cin >> s;
            auto sc = sys->findScenario(s);
            if (sc) r->registerScenarioForEvent(t, sc);
        }
        if (c == 3) {
            std::string t; 
            std::cout << "Тип события: ";
            std::cin >> t;
            r->routeEvent(t);
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "");
    auto sys = std::make_shared<SmartHomeSystem>();
    auto router = std::make_shared<EventRouter>();

    while (true) {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
        std::cout << "1 — Управление устройствами" << std::endl;
        std::cout << "2 — Управление сценариями" << std::endl;
        std::cout << "3 — Управление пользователями" << std::endl;
        std::cout << "4 — Энергия" << std::endl;
        std::cout << "5 — Уведомления" << std::endl;
        std::cout << "6 — События" << std::endl;
        std::cout << "0 — Выход" << std::endl;
        std::cout << "> ";
        int c;
        std::cin >> c;
        if (c == 0) break;
        if (c == 1) menuDevices(sys);
        if (c == 2) menuScenarios(sys);
        if (c == 3) menuUsers(sys);
        if (c == 4) menuEnergy(sys);
        if (c == 5) menuNotifications(sys);
        if (c == 6) menuEvents(router, sys);
    }
    return 0;
}