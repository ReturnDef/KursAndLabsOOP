#include "SmartHomeSystem.hpp"
#include "DeviceAction.hpp"
#include "Scenario.hpp"
#include "EventRouter.hpp"
#include "LogManager.hpp"
#include "NotificationCenter.hpp"
#include "Thermostat.hpp"

#include <iostream>
#include <algorithm>

SmartHomeSystem::SmartHomeSystem() {
    NotificationCenter::instance().subscribe([this](const Notification& n){
        notifications.push_back(std::make_shared<Notification>(n));
        std::cout << "[Уведомление] " << n.getMessage() << std::endl;
    });
}

SmartHomeSystem::~SmartHomeSystem() = default;


// -------------------------------------------------------------
//  Создание программных сценариев
// -------------------------------------------------------------
void SmartHomeSystem::createDefaultScenarios() {

    auto find = [this](const std::string& kw){
        for (auto& d : devices)
            if (d && d->getName().find(kw) != std::string::npos)
                return d;
        return std::shared_ptr<Device>(nullptr);
    };

    // ===== 1) Доброе утро =====
    auto morning = std::make_shared<Scenario>(
        "Доброе утро",
        "Включает свет, кофеварку и музыку."
    );

    if (auto light = find("Light"); light)
        morning->addAction(std::make_shared<DeviceAction>("Включить свет", light,
            [](auto d){ d->turnOn(); }));

    if (auto cf = find("Coffee"); cf)
        morning->addAction(std::make_shared<DeviceAction>("Запустить кофеварку", cf,
            [](auto d){ d->turnOn(); }));

    if (auto sp = find("Speaker"); sp)
        morning->addAction(std::make_shared<DeviceAction>("Включить музыку", sp,
            [](auto d){ d->turnOn(); }));

    addScenario(morning);

    // ===== 2) Умный климат =====
    auto climate = std::make_shared<Scenario>(
        "Умный климат", "Устанавливает комфортную температуру 23°C."
    );

    if (auto ac = find("Thermo"); ac)
        climate->addAction(std::make_shared<DeviceAction>("Установить 23°C", ac,
            [](auto d){
                if (auto t = std::dynamic_pointer_cast<Thermostat>(d))
                    t->setTargetTemp(22.0);

            }));

    addScenario(climate);

    // ===== 3) Безопасный дом =====
    auto safe = std::make_shared<Scenario>(
        "Безопасный дом", "Закрывает замки и включает сигнализацию."
    );

    if (auto lock = find("Lock"); lock)
        safe->addAction(std::make_shared<DeviceAction>("Закрыть замки", lock,
            [](auto d){ d->turnOn(); }));

    if (auto alarm = find("Alarm"); alarm)
        safe->addAction(std::make_shared<DeviceAction>("Включить охрану", alarm,
            [](auto d){ d->turnOn(); }));

    addScenario(safe);

    // ===== 4) Режим экономии =====
    auto eco = std::make_shared<Scenario>(
        "Режим экономии", "Снижает потребление всех устройств."
    );

    for (auto& d : devices) {
        if (!d) continue;
        eco->addAction(std::make_shared<DeviceAction>(
            "Снизить потребление: " + d->getName(), d,
            [](auto dev){ dev->scalePower(0.8); }
        ));
    }
    addScenario(eco);

    // ===== 5) Я ушёл из дома =====
    auto away = std::make_shared<Scenario>(
        "Я ушёл из дома", "Выключает устройства и включает охрану."
    );

    for (auto& d : devices)
        away->addAction(std::make_shared<DeviceAction>(
            "Выключить: " + d->getName(),
            d, [](auto dv){ dv->turnOff(); }
        ));

    if (auto alarm = find("Alarm"); alarm)
        away->addAction(std::make_shared<DeviceAction>("Включить сигнализацию", alarm,
            [](auto d){ d->turnOn(); }));

    addScenario(away);

    // ===== 6) Вечеринка =====
    auto party = std::make_shared<Scenario>(
        "Вечеринка", "Включает подсветку и громкую музыку."
    );

    if (auto sp = find("Speaker"); sp)
        party->addAction(std::make_shared<DeviceAction>("Музыка (Party Mode)", sp,
            [](auto d){ d->turnOn(); }));

    for (auto& d : devices)
        if (d && (d->getName().find("Light") != std::string::npos ||
                  d->getName().find("Свет")  != std::string::npos))
            party->addAction(std::make_shared<DeviceAction>(
                "Подсветка: " + d->getName(), d, [](auto dev){ dev->turnOn(); }
            ));

    addScenario(party);

    std::cout << "[OK] Программные сценарии зарегистрированы.\n";
}



// -------------------------------------------------------------
//  Управление устройствами, пользователями и уведомлениями
// -------------------------------------------------------------

void SmartHomeSystem::addDevice(std::shared_ptr<Device> d) {
    if (!d) return;
    if (d->getId() == 0) d->setId(++nextDeviceId);

    auto it = std::find_if(devices.begin(), devices.end(),
        [&](auto& x){ return x && x->getId() == d->getId(); });

    if (it == devices.end())
        devices.push_back(d);
}

void SmartHomeSystem::removeDevice(int id) {
    devices.erase(
        std::remove_if(devices.begin(), devices.end(),
            [&](auto& d){ return d && d->getId() == id; }),
        devices.end()
    );
}

std::shared_ptr<Device> SmartHomeSystem::findDevice(int id) const {
    for (auto& d : devices)
        if (d && d->getId() == id)
            return d;
    return nullptr;
}


void SmartHomeSystem::addScenario(std::shared_ptr<Scenario> s) {
    if (!s) return;
    if (s->getId() == 0) s->setId(++nextScenarioId);

    scenarios.push_back(s);
    std::cout << "Добавлен сценарий: " << s->getName()
              << " (id=" << s->getId() << ")\n";
}


void SmartHomeSystem::showNotifications() const {
    for (auto& n : notifications)
        if (n) n->show();
}

void SmartHomeSystem::sendNotificationToAll(const std::string& msg) {
    notifications.push_back(std::make_shared<Notification>(msg));
}

void SmartHomeSystem::clearNotifications() {
    notifications.clear();
}

// -------------------------------------------------------------
//     Управление пользователями
// -------------------------------------------------------------
void SmartHomeSystem::addUser(std::shared_ptr<User> u) {
    if (!u) return;
    if (u->getId() == 0) u->setId(++nextUserId);

    auto it = std::find_if(users.begin(), users.end(),
        [&](auto& x){ return x && x->getId() == u->getId(); });

    if (it == users.end())
        users.push_back(u);
}

void SmartHomeSystem::removeUser(int id) {
    users.erase(
        std::remove_if(users.begin(), users.end(),
            [&](auto& u){ return u && u->getId() == id; }),
        users.end()
    );
}

std::shared_ptr<User> SmartHomeSystem::findUser(int id) const {
    for (auto& u : users)
        if (u && u->getId() == id)
            return u;
    return nullptr;
}

std::vector<std::shared_ptr<User>> SmartHomeSystem::listUsers() const {
    return users;
}
