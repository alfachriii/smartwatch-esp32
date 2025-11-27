#include "HomeApp.hpp"
#include "../core/EventBus.hpp"
#include "../core/DisplayDriver.hpp"
#include "../core/UIManager.hpp"
#include "../services/Time.hpp"


namespace App {
  HomeApp::HomeApp(Core::EventBus* bus, Core::DisplayDriver* disp): eventBus(bus), display(disp) {
    this->latestHour = 0;
    this->latestMinute = 0;
  }

  void HomeApp::setUi(Core::UIManager* ui) { this->ui = ui; }

  void HomeApp::onEnter() {
    display->homePage();
    
    eventBus->subscribe(Core::EventType::TIME_UPDATE, [this](void *data) {
      auto* pData = static_cast<Service::TimePayload*>(data);

      this->latestHour = pData->hour;
      this->latestMinute = pData->minute;

      ui->requestRender(); });
  }

  void HomeApp::render() {
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d", this->latestHour, this->latestMinute);

    display->showTime(buf);
  }
}