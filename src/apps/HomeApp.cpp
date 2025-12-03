#include "HomeApp.hpp"
#include "config.h"
#include "../core/EventBus.hpp"
#include "../core/DisplayDriver.hpp"
#include "../core/UIManager.hpp"
#include "../services/TimeService.hpp"


namespace App {
  HomeApp::HomeApp(Core::EventBus* bus, Core::DisplayDriver* disp): eventBus(bus), display(disp) {
    this->latestTime.hour = 0;
    this->latestTime.minute = 0;
    this->spriteClock = nullptr;
  }

  void HomeApp::onEnter() {
    //display render
    display->fillScreen(BG_COLOR);
    display->setTextColor(TEXT_COLOR);

    this->spriteClock = display;
    spriteClock.createSprite(240, 80);

    // subscribe event
    eventBus->subscribe(Core::EventType::TIME_UPDATE, [this](void *data) {
      auto* pData = static_cast<Service::Times*>(data);

      this->latestTime = *pData;

      ui->requestRender(); 
    });
  }

  void HomeApp::render() {
    char timeBuf[16];
    snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d", this->latestTime.hour, this->latestTime.minute);

    spriteClock.fillSprite(TFT_BLUE);
    spriteClock.setTextColor(TEXT_COLOR);
    spriteClock.setTextSize(3);
    spriteClock.setTextDatum(textdatum_t::middle_center);
    spriteClock.drawString(timeBuf, spriteClock.width() / 2, spriteClock.height() / 2);
    spriteClock.pushSprite(0, 80);
  }

  void HomeApp::onButton(Service::ButtonPayload btn) {
    if(btn.id == Service::ButtonID::BTN_SELECT && btn.event == Service::ButtonEvent::Click) {
      ui->switchTo(Core::UiState::SETTINGS_MENU);
    }
  }
}