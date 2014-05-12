#pragma once

#include <functional>

namespace prz {
    namespace utils {
        class INotificationCenter {
        public:
            typedef std::function<void(void*)> ZNotificationEventHandler;

            virtual void AddObserver(const std::string& name, void* observerOwner, ZNotificationEventHandler handler) = 0;
            virtual void RemoveObserver(const std::string& name, void* observerOwner) = 0;

            virtual void PostNotification(const std::string& name) = 0;
            virtual void PostNotification(const std::string& name, void* params) = 0;
        };
    }
}
