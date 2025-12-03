#pragma once
#include <map>
#include <vector>
#include <functional>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>


namespace Core {
  enum class EventType {
      TIME_UPDATE,
      SENSOR_UPDATE,
      BLE_ON_CONNECT,
      BLE_ON_DISCONNECT,
      BLE_ON_PASSKEY,
      BLE_ON_AUTH_COMP,
      BATT_UPDATE,
  };
  
  struct EventItem {
      EventType type;
      void* data;
  };
  
  using EventCallback = std::function<void(void *)>;
  
  class EventBus {
  public:
      EventBus();
      ~EventBus();
      void begin();

      void subscribe(EventType type, EventCallback callback);
      void publish(EventType type, void* data = nullptr);
  
  private:
      TaskHandle_t eventTaskHandle = nullptr;

      static void eventTask(void* pvParams);
      void dispatch(EventItem item);
  
      std::map<EventType, std::vector<EventCallback>> listeners;
      QueueHandle_t queue;
  };
  
};
