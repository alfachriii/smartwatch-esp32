#include "UIManager.hpp"
#include "EventBus.hpp"
#include "../apps/HomeApp.hpp"
#include "../apps/SettingsApp.hpp"
#include "../apps/BluetoothApp.hpp"

namespace Core {
  UIManager::UIManager(EventBus* bus): 
    eventBus(bus) {

    this->currentApp = nullptr;
    this->uiStack.push_back(Core::UiState::HOME_MENU);
    this->renderRequested = true;
  }

  UIManager::~UIManager() {
    if (uiTaskHandle != nullptr) {
      vTaskDelete(uiTaskHandle);
      uiTaskHandle = nullptr;
    }

    delete homeApp;
    delete settingsApp;
  }

  void UIManager::init() {
    display.init();

    this->homeApp = new App::HomeApp(eventBus, &display);
    this->bluetoothApp = new App::BluetoothApp(eventBus, &display);

    homeApp->setUi(this);
    bluetoothApp->setUi(this);

    switchTo(UiState::HOME_MENU, true);

    xTaskCreatePinnedToCore(
      uiTaskEntry, "UiTask", 4096, this, 1, &uiTaskHandle, 1
    );
  }

  void UIManager::uiTaskEntry(void* pv) {
    auto* self = static_cast<UIManager*>(pv);
    self->uiTask();
  }

  void UIManager::requestRender() {
    this->renderRequested = true;
  }

  void UIManager::uiTask() {
    while (true) {
      if (renderRequested) {
        renderRequested = false;
        if (currentApp) currentApp->render();
      }
        vTaskDelay(pdMS_TO_TICKS(16)); // ~60fps
    }
  }

  void UIManager::back() {
    if(uiStack.size() > 1) uiStack.pop_back();

    this->switchTo(uiStack.back(), false);
  }

  void UIManager::switchTo(UiState newState, bool isPush) {
    if (currentApp) currentApp->onExit();

    uiStack.push_back(newState);
    
    switch (uiStack.back()) {
      case UiState::HOME_MENU:
        this->currentApp = homeApp;
        break;
      case UiState::SETTINGS_MENU:
        this->currentApp = settingsApp;
        break;
      case UiState::BLUETOOTH_MENU:
        this->currentApp = bluetoothApp;
        break;
      }

    currentApp->onEnter();
    requestRender();
  }

  void UIManager::dispatchButton(Service::ButtonPayload payload) {
    if (currentApp) {
        currentApp->onButton(payload);
    }
  } 

  
}
