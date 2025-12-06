#include "SmartHomeController.hpp"
#include <algorithm>
#include <iostream>

int SmartHomeController::addDevice(const std::string &name){
    SimpleDevice d;
    d.id = nextDeviceId++;
    d.name = name;
    devices.push_back(d);
    log("Device added: " + name);
    return d.id;
}

bool SmartHomeController::removeDevice(int id){
    auto it = std::find_if(devices.begin(), devices.end(), [&](const SimpleDevice& sd){ return sd.id==id; });
    if(it==devices.end()) return false;
    log("Device removed: " + it->name);
    devices.erase(it);
    return true;
}

SimpleDevice* SmartHomeController::findDeviceById(int id){
    auto it = std::find_if(devices.begin(), devices.end(), [&](SimpleDevice &sd){ return sd.id==id; });
    if(it==devices.end()) return nullptr;
    return &(*it);
}

SimpleDevice* SmartHomeController::findDeviceByName(const std::string &name){
    auto it = std::find_if(devices.begin(), devices.end(), [&](SimpleDevice &sd){ return sd.name==name; });
    if(it==devices.end()) return nullptr;
    return &(*it);
}

std::vector<SimpleDevice>& SmartHomeController::listDevices(){ return devices; }

int SmartHomeController::addScenario(const std::string &name){
    SimpleScenario s;
    s.id = nextScenarioId++;
    s.name = name;
    scenarios.push_back(s);
    log("Scenario added: " + name);
    return s.id;
}

SimpleScenario* SmartHomeController::getScenario(int id){
    auto it = std::find_if(scenarios.begin(), scenarios.end(), [&](SimpleScenario &ss){ return ss.id==id; });
    if(it==scenarios.end()) return nullptr;
    return &(*it);
}

std::vector<SimpleScenario>& SmartHomeController::listScenarios(){ return scenarios; }

void SmartHomeController::runScenario(int id){
    auto s = getScenario(id);
    if(!s) { log("Tried to run missing scenario id=" + std::to_string(id)); return; }
    log("Running scenario: " + s->name);
    for(auto &a : s->actions) {
        a();
    }
}

void SmartHomeController::log(const std::string &msg){
    logs.push_back(msg);
    std::cout << "[LOG] " << msg << std::endl;
}

const std::vector<std::string>& SmartHomeController::getLogs() const { return logs; }
