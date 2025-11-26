#pragma once
#include "DisplayDriver.hpp"
#include "EventBus.hpp"
#include "BaseApp.hpp"
#include "../apps/HomeApp.hpp"

namespace Core{

  enum class UiState {
      HOME_MENU,
      SETTINGS_MENU,
  };
  
  class UIManager {
    public:
      UIManager(EventBus* eventBus);
      void init();
      void switchTo(UiState newState);
      void requestRender();

    private:
      EventBus* eventBus;
      DisplayDriver display;

      UiState currentState;
      BaseApp* currentApp;

      App::HomeApp homeApp;

      volatile bool renderRequested;

      static void uiTaskEntry(void *pv);
      void uiTask();
  };
}