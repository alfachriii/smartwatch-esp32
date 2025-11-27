#pragma once
#include "DisplayDriver.hpp"
#include "EventBus.hpp"
#include "BaseApp.hpp"

namespace App {
  class HomeApp;
}

namespace Core{

  enum class UiState {
      HOME_MENU,
      SETTINGS_MENU,
  };
  
  class UIManager {
    public:
      UIManager(EventBus* eventBus);
      ~UIManager();
      void init();
      void switchTo(UiState newState);
      void requestRender();

    private:
      TaskHandle_t uiTaskHandle = nullptr;
      EventBus* eventBus;
      DisplayDriver display;

      UiState currentState;
      BaseApp* currentApp;

      App::HomeApp* homeApp;

      volatile bool renderRequested;

      static void uiTaskEntry(void *pv);
      void uiTask();
  };
}