#pragma once
#include "DisplayDriver.hpp"
#include "EventBus.hpp"
#include "BaseApp.hpp"
#include <etl/vector.h>
#include <etl/array.h>

namespace App {
  class HomeApp;
  class SettingsApp;
  class BluetoothApp;
}

namespace Core{

  enum class UiState {
      HOME_MENU,
      SETTINGS_MENU,
      BLUETOOTH_MENU
  };
  
  class UIManager {
    public:
      UIManager(EventBus* eventBus);
      ~UIManager();
      void init();
      void switchTo(UiState newState, bool isPush);
      void back();
      void requestRender();
      void dispatchButton(Service::ButtonPayload payload);

    private: 
      TaskHandle_t uiTaskHandle = nullptr;
      EventBus* eventBus;
      DisplayDriver display;

      etl::vector<UiState, 10> uiStack;
      UiState currentState;
      BaseApp* currentApp;

      App::HomeApp* homeApp;
      App::SettingsApp* settingsApp;
      App::BluetoothApp* bluetoothApp;

      volatile bool renderRequested;

      static void uiTaskEntry(void *pv);
      void uiTask();
  };
}