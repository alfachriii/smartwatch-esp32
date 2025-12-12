#include "TimeService.hpp"
#include <Wire.h>
#include <Arduino.h>


namespace Service {

  Time::Time(Core::EventBus* bus): eventBus(bus), taskHandle(nullptr) {

  }

  void Time::init() {
    Wire.begin(8, 9);

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

  void Time::taskEntry(void *pvParameters) {
    Time* service = static_cast<Time*>(pvParameters);
    service->run();
  }

  void Time::run() {
    while (true) {
    if(!rtc.begin()) {
      Times payload;
      payload.hour = 5;
      payload.minute = 5;
      payload.second = 5;
    }

    DateTime now = rtc.now();

    Times payload;
    payload.hour = now.hour();
    payload.minute = now.minute();
    payload.second = now.second();

    eventBus->publish(Core::EventType::TIME_UPDATE, &payload);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  }
}