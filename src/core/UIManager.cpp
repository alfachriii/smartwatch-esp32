#include "UIManager.hpp"
#include "EventBus.hpp"
#include "../apps/HomeApp.hpp"

namespace Core {
  UIManager::UIManager(EventBus* bus): 
    eventBus(bus) {

    this->currentApp = nullptr;
    this->currentState = UiState::HOME_MENU;
    this->renderRequested = true;
  }

  UIManager::~UIManager() {
    if (uiTaskHandle != nullptr) {
      vTaskDelete(uiTaskHandle);
      uiTaskHandle = nullptr;
    }

    delete homeApp;
  }

  void UIManager::init() {
    display.init();

    this->homeApp = new App::HomeApp(eventBus, &display);

    homeApp->setUi(this);

    switchTo(UiState::HOME_MENU);

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

  void UIManager::switchTo(UiState newState) {
    if (currentApp) currentApp->onExit();
      currentState = newState;

      switch (newState) {
        case UiState::HOME_MENU:
          currentApp = homeApp;
          break;
      }

      currentApp->onEnter();
      requestRender();
  }
}
