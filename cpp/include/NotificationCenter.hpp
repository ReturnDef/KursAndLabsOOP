#pragma once
#include "Notification.hpp"
#include <functional>
#include <vector>
#include <mutex>

class NotificationCenter {
public:
    using Callback = std::function<void(const Notification&)>;

    static NotificationCenter& instance() {
        static NotificationCenter inst;
        return inst;
    }

    void subscribe(Callback cb) {
        std::lock_guard<std::mutex> lk(mutex_);
        subscribers.push_back(cb);
    }

    void notify(const Notification& n) {
        std::lock_guard<std::mutex> lk(mutex_);
        for (auto &s : subscribers) {
            if (s) s(n);
        }
    }

private:
    NotificationCenter() = default;
    ~NotificationCenter() = default;
    NotificationCenter(const NotificationCenter&) = delete;
    NotificationCenter& operator=(const NotificationCenter&) = delete;

    std::vector<Callback> subscribers;
    std::mutex mutex_;
};
