#pragma once
#include "../core/EventBus.hpp"
#include "RTClib.h"

namespace Service {
  struct Times{
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t second = 0;
  };
  
  class Time {
    public:
      Time(Core::EventBus* bus);
      void init();
  
    private:
      Core::EventBus* eventBus;
      TaskHandle_t taskHandle;
      RTC_DS3231 rtc;

      static void taskEntry(void* pvParameters);
      void run();
  };
}
