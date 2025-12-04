#include "BluetoothApp.hpp"
#include "config.h"

namespace App {
  BluetoothApp::BluetoothApp(Core::EventBus *bus, Core::DisplayDriver *disp): eventBus(bus), display(disp) {};

  void BluetoothApp::onEnter() {
    // subscribe to event
    eventBus->subscribe(Core::EventType::TIME_UPDATE, this, [this](void *data) {
      Service::Times *updatedData = static_cast<Service::Times*>(data); 
      this->latestTime = *updatedData;
      
      ui->requestRender();
    });

    eventBus->subscribe(Core::EventType::BATT_UPDATE, this, [this](void *data) {
      float *updatedData = static_cast<float*>(data); 
      this->latestBattPercent = *updatedData;
      
      ui->requestRender();
    });

    // ui button init
    Ui::UIButton backButton(display, Ui::UIButtonType::BACK_BUTTON);
    this->uiButtons[0] = &backButton;

    display->fillScreen(BG_COLOR);
  }

  void BluetoothApp::onExit() {
    eventBus->unsubscribe(Core::EventType::TIME_UPDATE, this);
    eventBus->unsubscribe(Core::EventType::BATT_UPDATE, this);

    this->selectedIndex = 0;
  }

  void BluetoothApp::render() {
    char timeBuf[16];
    snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d", this->latestTime.hour, this->latestTime.minute);

    display->renderStatusBar(timeBuf, this->latestBattPercent);
  }

  void BluetoothApp::onButton(Service::ButtonPayload btn) {
    if(btn.id == Service::ButtonID::BTN_NEXT && btn.event == Service::ButtonEvent::Click) {
      if(this->selectedIndex == 2) {
        this->selectedIndex = 0;

        ui->requestRender();
        return;
      }

      this->selectedIndex++;
      return;
    }

    if(btn.id == Service::ButtonID::BTN_BACK && btn.event == Service::ButtonEvent::Click) {
      if(this->selectedIndex == 0) {
        this->selectedIndex = 2;

        ui->requestRender();
        return;
      }

      this->selectedIndex = -1;
      return;
    }
  }
}