#pragma once
#include <map>
#include <vector>
#include <unordered_map>
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

  struct Listener {
    void* owner;
    EventCallback callback;
  };
  
  using EventCallback = std::function<void(void *)>;
  
  class EventBus {
  public:
      EventBus();
      ~EventBus();
      void begin();

      void subscribe(EventType type, void *owner, EventCallback cb);
      void unsubscribe(EventType type, void* owner);
      void publish(EventType type, void* data = nullptr);
  
  private:
      TaskHandle_t eventTaskHandle = nullptr;

      static void eventTask(void* pvParams);
      void dispatch(EventItem item);
  
      std::unordered_map<EventType, std::vector<Listener>> listeners;
      QueueHandle_t queue;
  };
  
};
