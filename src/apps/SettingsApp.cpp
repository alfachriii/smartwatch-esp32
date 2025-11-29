#include "SettingsApp.hpp"
#include "../core/UIManager.hpp"

namespace App {
  SettingsApp::SettingsApp(Core::EventBus* bus, Core::DisplayDriver* disp): eventBus(bus), display(disp) {}

  void SettingsApp::onEnter() {
    display->settingsPage();

  }

  void SettingsApp::render() {
    
  }

  void SettingsApp::onButton(Service::ButtonPayload btn) {
    if(btn.id == Service::ButtonID::BTN_BACK && btn.event == Service::ButtonEvent::Click) ui->back();

  }
}