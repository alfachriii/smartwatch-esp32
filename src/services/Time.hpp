#pragma once
#include "../core/EventBus.hpp"
#include "RTClib.h"

namespace Service{
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
