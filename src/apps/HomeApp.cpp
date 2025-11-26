#include "HomeApp.hpp"
#include "../core/EventBus.hpp"
#include "../core/DisplayDriver.hpp"


namespace App {
  HomeApp::HomeApp(Core::EventBus* bus, Core::DisplayDriver* disp): eventBus(bus), display(disp) {
    
  }

  void HomeApp::init() {
    eventBus->subscribe(Core::EventType::TIME_UPDATE, [this](void* data) {

    });
  }
}