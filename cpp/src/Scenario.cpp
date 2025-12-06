#include "Scenario.hpp"
#include "DeviceAction.hpp"

Scenario::Scenario(const std::string& name)
    : name(name) {}

void Scenario::addAction(std::shared_ptr<Action> act) {
    actions.push_back(act);
}

// совместимость со старой системой
void Scenario::execute() {
    run();
}

void Scenario::run() {
    std::cout << "\n=== Running Scenario: " << name << " (ID=" << id << ") ===\n";

    for (auto& act : actions) {
        act->execute();
    }

    std::cout << "=== Scenario finished ===\n\n";
}

void Scenario::showActions() const {
    std::cout << "\n--- Actions in Scenario '" << name << "' (ID=" << id << ") ---\n";

    for (const auto& a : actions) {
        std::cout << "* " << a->getName();
        auto da = std::dynamic_pointer_cast<DeviceAction>(a);
        if (da) std::cout << " (DeviceAction)";
        std::cout << "\n";
    }
}
