#include "WindowBlind.hpp"

WindowBlind::WindowBlind(int id, const std::string &name, const std::string &location)
    : Device(id, name, location), position(0) {}

WindowBlind::WindowBlind(const WindowBlind& other)
    : Device(other), position(other.position) {}

WindowBlind::~WindowBlind() {}

void WindowBlind::open() {
    position = 100;
    std::cout << "Жалюзи '" << getName() << "' открыты" << std::endl;
}

void WindowBlind::close() {
    position = 0;
    std::cout << "Жалюзи '" << getName() << "' закрыты" << std::endl;
}

void WindowBlind::setPosition(int p) {
    position = p;
    std::cout << "Жалюзи '" << getName() << "' установлена позиция: " << position << std::endl;
}

void WindowBlind::showStatus() {
    std::cout << "Жалюзи '" << getName() << "' позиция=" << position << std::endl;
}