#include "../core/EventBus.hpp"

namespace Service {
    class Wifi {
        public:
            Wifi(Core::EventBus *bus);
            void begin();
            void connect(bool isReconnect);
            void handleWifiEvent(WiFiEvent_t &event, WiFiEventInfo_t &info); 
        private:
            Core::EventBus *eventBus;
            TaskHandle_t taskHandle;
            int status;
            bool isConnecting;
            uint32_t connectStart;

            void wifiTaskEntry(void *pv);
            void wifiTask();
    };
}