#include "./services/Time.hpp"
#include "./core/EventBus.hpp"
#include "./core/UIManager.hpp"
#include "./core/DisplayDriver.hpp"

Core::EventBus eventBus;
Core::UIManager ui(&eventBus);
Service::Time timeService(&eventBus);

void setup() {
  eventBus.begin();
  ui.init();
  timeService.init();
}

void loop() {

}