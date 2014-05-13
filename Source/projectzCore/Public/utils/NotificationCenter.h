#pragma once

#include <unordered_map>
#include <vector>

#include "utils/INotificationCenter.h"

namespace prz {
    namespace utils {
        class ZNotificationCenter : public INotificationCenter {
        public:
            ZNotificationCenter();
            ZNotificationCenter(const ZNotificationCenter& other);
            ZNotificationCenter& operator=(const ZNotificationCenter& other);
            virtual ~ZNotificationCenter();

            virtual bool AddObserver(const std::string& name, void* observerOwner, ZNotificationEventHandler handler) override;
            virtual bool RemoveObserver(const std::string& name, void* observerOwner) override;

            virtual bool PostNotification(const std::string& name) override;
            virtual bool PostNotification(const std::string& name, const void* argument) override;

        private:
            struct ZObserver {
                void* observerOwner;
                ZNotificationEventHandler handler;

                ZObserver(void* observerOwner, ZNotificationEventHandler handler) {
                    this->observerOwner = observerOwner;
                    this->handler = handler;
                }
            };

            typedef std::vector<ZObserver> ZObserverList;
            typedef std::unordered_map<std::string, ZObserverList*> ZObserverListTable;
            typedef std::pair<std::string, ZObserverList*> ZObserverListTablePair;

            ZObserverListTable mObservers;
        };
    }
}
