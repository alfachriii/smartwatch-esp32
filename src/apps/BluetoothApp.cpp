#include "BluetoothApp.hpp"
#include "config.h"

namespace App {
  BluetoothApp::BluetoothApp(Core::EventBus *bus, Core::DisplayDriver *disp): eventBus(bus), display(disp) {};

  void BluetoothApp::onEnter() {
    display->fillScreen(BG_COLOR);
  }

  void BluetoothApp::onExit() {

    delete this;
  }

  void BluetoothApp::render() {

  }

  void BluetoothApp::onButton(Service::ButtonPayload btn) {

  }
}