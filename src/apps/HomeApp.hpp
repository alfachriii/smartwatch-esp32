#include "../core/EventBus.hpp"
#include "../core/DisplayDriver.hpp"
#include "../core/BaseApp.hpp"

namespace App {

  class HomeApp: public Core::BaseApp {
    public:
      HomeApp(Core::EventBus* bus, Core::DisplayDriver* disp);
      void init();
      void render();

    private:
      Core::EventBus* eventBus;
      Core::DisplayDriver* display;
  };
}