#include "./services/TimeService.hpp"
#include "./core/EventBus.hpp"
#include "./core/UIManager.hpp"
#include "./core/DisplayDriver.hpp"
#include "./services/ButtonService.hpp"
#include "./services/BleService.hpp"
#include "./services/WifiService.hpp"
#include <Arduino.h>

Core::EventBus eventBus;
Core::UIManager ui(&eventBus);
Service::BLE::Ble ble(&eventBus);
Service::Wifi wifi(&eventBus);
Service::Time timeService(&eventBus);
Service::Button buttonService;

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting....");

  buttonService.addButton(Service::ButtonID::BTN_SELECT, 2);
  buttonService.addButton(Service::ButtonID::BTN_BACK, 1);

  ble.begin();
  eventBus.begin();
  ui.init();

  buttonService.buttonCallback = [&](Service::ButtonPayload payload)
  {
    ui.dispatchButton(payload);
  };

  timeService.init();
}

void loop()
{
  buttonService.update();
  wifi.update();
}