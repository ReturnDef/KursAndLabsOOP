#pragma once
#include "Device.hpp"

class DoorLock : public Device {
public:
    DoorLock(int id = 0, const std::string &name = "DoorLock", const std::string &location = "");
    DoorLock(const DoorLock& other);
    ~DoorLock();
    void lock();
    void unlock();
    void alertIfForced();
    void showStatus() override;

private:
    bool isLocked;
};
