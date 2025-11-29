#pragma once
#include "../core/BaseApp.hpp"
#include "../core/DisplayDriver.hpp"
#include "../core/EventBus.hpp"
#include "../services/ButtonService.hpp"

namespace Core {
  class UIManager;
}

namespace App {
  class SettingsApp: public Core::BaseApp {
    public:
      SettingsApp(Core::EventBus *bus, Core::DisplayDriver *display);

      void render() override;
      void onEnter() override;
      void onButton(Service::ButtonPayload payload) override;

    private:
      Core::EventBus* eventBus;
      Core::DisplayDriver* display;
  };
}