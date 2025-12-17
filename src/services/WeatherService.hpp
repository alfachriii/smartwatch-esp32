#pragma once
#include "../core/EventBus.hpp"
#include "WifiService.hpp"

namespace Service {
  enum class WeatherState
  {
    IDLE,
    WAIT_WIFI,
    FETCHING,
    READY,
    FAILED
  };

  class Weather {
    public:
      Weather(Core::EventBus *bus);
      void init();
      void reqFetchWifi();
      void startFetchWifi();

    private:
      Core::EventBus *eventBus;
      WeatherState weatherState;
      WifiState wifiState;
  };
}