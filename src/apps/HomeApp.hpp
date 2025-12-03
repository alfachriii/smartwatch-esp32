#pragma once
#include "../core/EventBus.hpp"
#include "../core/DisplayDriver.hpp"
#include "../core/BaseApp.hpp"
#include "../services/ButtonService.hpp"
#include "../services/TimeService.hpp"

namespace Core {
  class UIManager;
  class BaseApp;
}

namespace App {

  class HomeApp: public Core::BaseApp {
    public:
      HomeApp(Core::EventBus* bus, Core::DisplayDriver* disp);

      void render() override;
      void onEnter() override;
      void onButton(Service::ButtonPayload payload) override;

    private:
      lgfx::LGFX_Sprite spriteClock;
      Core::EventBus* eventBus;
      Core::DisplayDriver* display;

      Service::Times latestTime;
  };
}