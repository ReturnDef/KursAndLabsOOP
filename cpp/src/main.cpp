#include "../include/SmartHomeSystem.hpp"
#include "../include/Light.hpp"
#include "../include/Heater.hpp"
#include "../include/DoorLock.hpp"
#include "../include/Camera.hpp"
#include "../include/Sprinkler.hpp"
#include "../include/WindowBlind.hpp"
#include "../include/Thermostat.hpp"
#include "../include/SmokeDetector.hpp"
#include "../include/EnergyMeter.hpp"
#include "../include/User.hpp"
#include "../include/Scenario.hpp"
#include "../include/Action.hpp"
#include <cstdio>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SmartHomeSystem sys;

    Light* l = new Light(1, "LampLiving", "Гостиная");
    Heater* h = new Heater(2, "MainHeater", "Коридор");
    DoorLock* dl = new DoorLock(3, "FrontDoor", "Вход");
    Camera* cam = new Camera(4, "PorchCam", "Крыльцо");
    Sprinkler* sp = new Sprinkler(6, "Sprinkler", "Сад");
    WindowBlind* wb = new WindowBlind(7, "WindowBlind", "Окно");
    Thermostat* th = new Thermostat(8, "Thermostat", "Коридор");
    SmokeDetector* sd = new SmokeDetector(9, "SmokeDetector", "Кухня");
    EnergyMeter* em = new EnergyMeter(5, "MainMeter", "Подвал");

    sys.addDevice(l); sys.addDevice(h); sys.addDevice(dl); sys.addDevice(cam);
    sys.addDevice(sp); sys.addDevice(wb); sys.addDevice(th); sys.addDevice(sd); sys.addDevice(em);

    sys.getEnergyManager().addMeter(em);

    User* u = new User("u1", "Alice");
    Action* a1 = new Action("TurnOnLight");
    Action* a2 = new Action("SetHeaterTemp");

    Scenario* s = new Scenario("MorningRoutine");
    s->addAction(a1);
    s->addAction(a2);

    u->executeScenario(s);

    em->updateUsage(15.75);

    sys.getScheduler().addTask(a1);
    sys.getScheduler().addTask(a2);

    sys.runDemo();

    delete a1; delete a2; delete s; delete u;
    delete l; delete h; delete dl; delete cam; delete sp; delete wb; delete th; delete sd; delete em;

    return 0;
}