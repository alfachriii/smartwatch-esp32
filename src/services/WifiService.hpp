#pragma once
#include "../core/EventBus.hpp"
#include "WiFi.h"

namespace Service {
  enum class WifiState
  {
    CONNECTING,
    FAIL_TO_CONNECT,
    CONNECTED,
    DISCONNECTED,
  };

  class Wifi
  {
  public:
    Wifi(Core::EventBus *bus);
    void init();
    int connect();
    void disconnect();
    uint16_t scan();
    void update();
    void handleWeatherFetchReq();

    WifiState state;
    
    private:
    Core::EventBus *eventBus;
    uint32_t connectStart;
    static Wifi *wifiInstance;

    static void handleWifiEvent(WiFiEvent_t &event, WiFiEventInfo_t &info);
  };
}