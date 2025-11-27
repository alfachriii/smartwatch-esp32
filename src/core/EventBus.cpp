#include "EventBus.hpp"

namespace Core {

  EventBus::EventBus() {
      queue = xQueueCreate(10, sizeof(EventItem)); // buffer 10 event
  }

  EventBus::~EventBus() {
    if (eventTaskHandle) {
        vTaskDelete(eventTaskHandle);
    }

    if (queue) {
        vQueueDelete(queue);
    }
  }
  
  void EventBus::begin() {
      xTaskCreatePinnedToCore(eventTask, "EventTask", 4096, this, 1, &eventTaskHandle, 0);
  }
  
  void EventBus::subscribe(EventType type, EventCallback callback) {
      listeners[type].push_back(callback);
  }
  
  void EventBus::publish(EventType type, void* data) {
      EventItem item{type, data};
      xQueueSend(queue, &item, 0);
  }
  
  void EventBus::eventTask(void* pvParams) {
      auto* bus = static_cast<EventBus*>(pvParams);
      EventItem item;
  
      while (true) {
          if (xQueueReceive(bus->queue, &item, portMAX_DELAY) == pdTRUE) {
              bus->dispatch(item);
          }
      }
  }
  
  void EventBus::dispatch(EventItem item) {
      auto it = listeners.find(item.type);
      if (it != listeners.end()) {
          for (auto& cb : it->second) {
              cb(item.data);
          }
      }
  }

}
