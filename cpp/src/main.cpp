#include "../include/SmartHomeSystem.hpp"
#include "../include/Device.hpp"
#include "../include/Light.hpp"
#include "../include/Heater.hpp"
#include "../include/DoorLock.hpp"
#include "../include/Camera.hpp"
#include "../include/Sprinkler.hpp"
#include "../include/WindowBlind.hpp"
#include "../include/Thermostat.hpp"
#include "../include/SmokeDetector.hpp"
#include "../include/EnergyMeter.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <locale>

void clearInput() {
    std::cin.clear();
    std::string tmp;
    std::getline(std::cin, tmp);
}

int getInt(const std::string& msg) {
    int x;
    while (true) {
        std::cout << msg;
        if (std::cin >> x) {
            clearInput();
            return x;
        }
        std::cout << "Ошибка ввода. Повторите.\n";
        clearInput();
    }
}

void menu(SmartHomeSystem& sys) {

    while (true) {
        std::cout << "\n===== МЕНЮ УМНОГО ДОМА =====\n";
        std::cout << "1. Создать устройство\n";
        std::cout << "2. Создать действие\n";
        std::cout << "3. Создать сценарий\n";
        std::cout << "4. Добавить действие в сценарий\n";
        std::cout << "5. Запустить сценарий\n";
        std::cout << "6. Показать устройства, сценарии, действия\n";
        std::cout << "7. Отправить уведомление устройству\n";
        std::cout << "8. Показать журнал уведомлений\n";
        std::cout << "0. Выход\n> ";

        int c;
        if (!(std::cin >> c)) {
            clearInput();
            std::cout << "Ошибка ввода.\n";
            continue;
        }
        clearInput();

        if (c == 0) {
            std::cout << "Выход...\n";
            return;
        }

        if (c == 1) {
            std::cout << "Выберите тип устройства:\n";
            std::cout << "1. Light\n2. Heater\n3. DoorLock\n4. Camera\n"
                         "5. Sprinkler\n6. WindowBlind\n7. Thermostat\n"
                         "8. SmokeDetector\n9. EnergyMeter\n> ";

            int t;
            std::cin >> t;
            clearInput();

            int id = getInt("ID устройства: ");

            std::string name, loc;
            std::cout << "Название: ";
            std::getline(std::cin, name);
            std::cout << "Локация: ";
            std::getline(std::cin, loc);

            std::shared_ptr<Device> dev;

            switch(t) {
                case 1: dev = std::make_shared<Light>(id, name, loc); break;
                case 2: dev = std::make_shared<Heater>(id, name, loc); break;
                case 3: dev = std::make_shared<DoorLock>(id, name, loc); break;
                case 4: dev = std::make_shared<Camera>(id, name, loc); break;
                case 5: dev = std::make_shared<Sprinkler>(id, name, loc); break;
                case 6: dev = std::make_shared<WindowBlind>(id, name, loc); break;
                case 7: dev = std::make_shared<Thermostat>(id, name, loc); break;
                case 8: dev = std::make_shared<SmokeDetector>(id, name, loc); break;
                case 9: dev = std::make_shared<EnergyMeter>(id, name, loc); break;
                default:
                    std::cout << "Неизвестный тип.\n";
                    continue;
            }

            sys.addDevice(dev);
            std::cout << "Устройство создано!\n";
        }

        else if (c == 2) {
            std::string name;
            std::cout << "Название действия: ";
            std::getline(std::cin, name);

            auto act = std::make_shared<Action>(name);
            sys.addAction(act);

            std::cout << "Действие создано!\n";
        }

        else if (c == 3) {
            std::string name;
            std::cout << "Название сценария: ";
            std::getline(std::cin, name);

            auto sc = std::make_shared<Scenario>(name);
            sys.addScenario(sc);

            std::cout << "Сценарий создан!\n";
        }

        else if (c == 4) {
            std::string s, a;
            std::cout << "Имя сценария: ";
            std::getline(std::cin, s);
            std::cout << "Имя действия: ";
            std::getline(std::cin, a);

            auto sc = sys.findScenario(s);
            auto ac = sys.findAction(a);

            if (!sc) std::cout << "Сценарий не найден.\n";
            else if (!ac) std::cout << "Действие не найдено.\n";
            else {
                sc->addAction(ac);
                std::cout << "Добавлено!\n";
            }
        }

        else if (c == 5) {
            std::string s;
            std::cout << "Имя сценария: ";
            std::getline(std::cin, s);

            auto sc = sys.findScenario(s);

            if (!sc) std::cout << "Сценарий не найден.\n";
            else sc->execute();
        }

        else if (c == 6) {
            sys.showDevices();
            sys.showScenarios();
            sys.showActions();
        }

        else if (c == 7) {
            int id = getInt("ID устройства: ");

            std::string msg;
            std::cout << "Сообщение: ";
            std::getline(std::cin, msg);

            sys.sendNotificationToDevice(id, msg);
        }

        else if (c == 8) {
            sys.showNotifications();
        }

        else {
            std::cout << "Неверный пункт меню.\n";
        }
    }
}

int main() {

    std::setlocale(LC_ALL, "Russian");

    SmartHomeSystem system;

    std::cout << "Добро пожаловать в систему умного дома!\n";

    menu(system);

    return 0;
}
