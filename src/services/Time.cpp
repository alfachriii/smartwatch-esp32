#include "Time.hpp"
#include <Wire.h>


namespace Service {

  struct TimePayload{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
  };

  Time::Time(Core::EventBus* bus): eventBus(bus), taskHandle(nullptr) {

  }

  void Time::init() {
    Wire.begin(21, 22);

    this->rtc.begin();

    xTaskCreate(
        Time::taskEntry,
        "TimeServiceTask",
        2048,
        this,
        1,
        &taskHandle
    );
  }

  void Time::taskEntry(void* pvParameters) {
    Time* service = static_cast<Time*>(pvParameters);
    service->run();
  }

  void Time::run() {
    DateTime now = rtc.now();

    TimePayload payload;
    payload.hour = now.hour();
    payload.minute = now.minute();
    payload.second = now.second();

    eventBus->publish(Core::EventType::TIME_UPDATE, &payload);
  }
}