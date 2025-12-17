#include "WifiService.hpp"
#include "config.h"
#include "WiFi.h"

namespace Service
{
    Wifi::Wifi(Core::EventBus *bus) : eventBus(bus), state(WifiState::DISCONNECTED) {
      wifiInstance = this;
    };

    void Wifi::init()
     {
        WiFi.mode(WIFI_STA);

        eventBus->subscribe(Core::EventType::CONNECT_TO_WIFI, this, [this](void *data)
                            { this->connect(); });

        eventBus->subscribe(Core::EventType::DISCONNECT_FROM_WIFI, this, [this](void *data)
                            { this->disconnect(); });

        eventBus->subscribe(Core::EventType::WEATHER_FETCH_WIFI, this, [this](void *data)
                            { this->handleWeatherFetchReq(); });
     }

    int Wifi::connect()
    {
      WiFi.begin(WIFI_SSID, WIFI_PASSWD);

      this->connectStart = millis();
      this->state = WifiState::CONNECTING;
    }

    void Wifi::disconnect() { WiFi.disconnect(); };

    uint16_t Wifi::scan() { return WiFi.scanNetworks(); };

    void Wifi::update() { //    <--- Called in main.cpp loop.
      if (!(state == WifiState::CONNECTING))
        return;

      if (millis() - connectStart > 3000) {
        WiFi.disconnect();
        this->state = WifiState::FAIL_TO_CONNECT;
        eventBus->publish(Core::EventType::WIFI_FAILED);
      }
    }

    void Wifi::handleWifiEvent(WiFiEvent_t &wifiEvent, WiFiEventInfo_t &wifiInfo)
    {
      if(!wifiInstance)
        return;
      
      switch (wifiEvent)
      {
      case SYSTEM_EVENT_STA_CONNECTED:
        wifiInstance->state = WifiState::CONNECTED;
        wifiInstance->eventBus->publish(Core::EventType::WIFI_CONNECTED);
        break;

      case SYSTEM_EVENT_STA_DISCONNECTED:
        wifiInstance->state = WifiState::DISCONNECTED;
        wifiInstance->eventBus->publish(Core::EventType::WIFI_DISCONNECTED);
        break;

      default:
        break;
      }
    }

    void Wifi::handleWeatherFetchReq() {
      if(!(this->state == WifiState::DISCONNECTED))
        eventBus->publish(Core::EventType::WIFI_FAILED);

      // TODO: fetching weather api.
      // TODO: publish response to eventBus
    }
}