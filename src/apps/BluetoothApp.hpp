#pragma once
#include "../core/BaseApp.hpp"
#include "../core/DisplayDriver.hpp"
#include "../core/EventBus.hpp"
#include "../services/ButtonService.hpp"
#include "../services/TimeService.hpp"
#include "../core/UIManager.hpp"
#include "../ui/UiButton.hpp"

namespace Core {
  class UIManager;
  class BaseApp;
}

namespace App {
  class BluetoothApp: public Core::BaseApp {
    public:
      BluetoothApp(Core::EventBus *bus, Core::DisplayDriver *display);

      void render() override;
      void onEnter() override;
      void onExit() override;
      void onButton(Service::ButtonPayload payload) override;

    private:
      Core::EventBus* eventBus;
      Core::DisplayDriver* display;

      Service::Times latestTime;
      float latestBattPercent;
  };
}