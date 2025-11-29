#pragma once
#include <Arduino.h>
#include "../core/EventBus.hpp"

namespace Service {
  enum class ButtonID {
    BTN_NEXT,
    BTN_BACK,
    BTN_SELECT
};

enum class ButtonEvent {
    Click,
    LongPress,
    DoubleClick
};

struct ButtonPayload {
    ButtonID id;
    ButtonEvent event;
};

  class Button {
    public:
      using ButtonCallback = std::function<void(ButtonPayload)>;
      ButtonCallback buttonCallback;

      void addButton(ButtonID type, uint8_t pin);
      void update();

    private:
      struct Btn {
        ButtonID id;
        uint8_t pin;
        bool lastState = true;   // pull-up: idle = HIGH
        uint32_t pressTime = 0;
        uint32_t lastClickTime = 0;
        bool waitingSecondClick = false;
      };

      Btn buttons[8];
      uint8_t buttonCount = 0;

      void handleButton(Btn &b);
      static constexpr uint32_t debounceTime = 80;
      static constexpr uint32_t longPressTime = 800;
  };
}