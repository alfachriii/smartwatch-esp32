#include <Arduino.h>
#include "ButtonService.hpp"
#include "../core/EventBus.hpp"

namespace Service {
  void Button::addButton(ButtonID id, uint8_t pin) {
    if (buttonCount >= 8) return;

    pinMode(pin, INPUT_PULLUP);

    this->buttons[buttonCount].id = id;
    this->buttons[buttonCount].pin = pin;
    this->buttons[buttonCount].lastState = true;

    this->buttonCount++;
  }

  void Button::update() {
    for (uint8_t i = 0; i < this->buttonCount; i++) {
        handleButton(this->buttons[i]);
    }
  }

  void Button::handleButton(Btn &btn) {
    bool state = digitalRead(btn.pin); // HIGH = idle, LOW = pressed
    uint32_t now = millis();

    // Deteksi press
    if (state == LOW && btn.lastState == HIGH) {
        btn.pressTime = now;
    }

    // Deteksi release
    if (state == HIGH && btn.lastState == LOW) {
        uint32_t pressDuration = now - btn.pressTime;

        // Long press
        if (pressDuration >= longPressTime) {
            if (buttonCallback) buttonCallback({ btn.id, ButtonEvent::LongPress });
            Serial.println("LongPress");
            btn.waitingSecondClick = false;
            btn.lastState = state;
            return;
        }

        if (btn.waitingSecondClick) {
            if (now - btn.lastClickTime <= 450) {
                if (buttonCallback) buttonCallback({ btn.id, ButtonEvent::DoubleClick });
                Serial.println("DoubleClick");
            }
            btn.waitingSecondClick = false;
            btn.lastState = state;
            return;
        }

        btn.waitingSecondClick = true;
        btn.lastClickTime = now;
        btn.lastState = state;
        return;
    }

    // Fallback click
    if (state == HIGH && btn.waitingSecondClick && (now - btn.lastClickTime > 300)) {
        if (buttonCallback) buttonCallback({ btn.id, ButtonEvent::Click });
        Serial.println("Click");
        btn.waitingSecondClick = false;
    }

    btn.lastState = state;
}

}