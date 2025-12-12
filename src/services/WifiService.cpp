#include "WifiService.hpp"
#include "config.h"
#include "WiFi.h"

namespace Service
{
    Wifi::Wifi(Core::EventBus *bus) : eventBus(bus) {

    };

    void Wifi::begin()
    {

        WiFi.mode(WIFI_STA);

        xTaskCreate(wifiTaskEntry, "WifiTask", 2048, this, 2, &taskHandle);

        eventBus->subscribe(Core::EventType::WIFI_DISCONNECTED, this, [this](void *data)
                            { this->connect(false); })
    }

    void Wifi::wifiTaskEntry(void *pvParameters)
    {
        Wifi *service = static_cast<Wifi *>(pvParameters);
        service->wifiTask();
    }

    void Wifi::wifiTask()
    {
        for (;;)
        {
            if (isConnecting)
            {
                uint32_t now = millis();

                if (now - connectStart > 5000)
                {
                    this->isConnecting = false;

                    eventBus->publish(Core::EventType::WIFI_UNABLE_TO_CONNECT, nullptr);
                }
            }

            vTaskDelay(10);
        }
    }

    void Wifi::connect(bool isReconnect)
    {
        connecting = true;
        connectStart = millis();

        this->status = WiFi.begin(WIFI_SSID, WIFI_PASSWD);

        if (this->status != WL_CONNECTED)
        {
            eventBus->publish(Core::EventType::WIFI_NOT_CONNECTED, nullptr);
            return;
        }

        eventBus->publish(Core::EventType::WIFI_CONNECTED, nullptr);
    }

    void Wifi::handleWifiEvent(WiFiEvent_t &wifiEvent, WiFiEventInfo_t &wifiInfo)
    {
        switch (wifiEvent)
        {
        case SYSTEM_EVENT_STA_CONNECTED:
            eventBus->publish(Core::EventType::WIFI_CONNECTED, nullptr);
            break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
            eventBus->publish(Core::EventType::WIFI_DISCONNECTED, nullptr);
            break;

        default:
            break;
        }
    }
}