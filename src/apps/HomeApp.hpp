#include "../core/EventBus.hpp"
#include "../core/DisplayDriver.hpp"
#include "../core/BaseApp.hpp"

namespace Core {
  class UIManager;
}

namespace App {

  class HomeApp: public Core::BaseApp {
    public:
      HomeApp(Core::EventBus* bus, Core::DisplayDriver* disp);
      void setUi(Core::UIManager *ui);
      void render() override;
      void onEnter() override;
      // void onExit() override;

    private:
      Core::EventBus* eventBus;
      Core::DisplayDriver* display;
      Core::UIManager* ui = nullptr;

      uint8_t latestHour;
      uint8_t latestMinute;
  };
}