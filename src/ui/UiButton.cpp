#include "UiButton.hpp"
#include "../core/DisplayDriver.hpp"

namespace Ui {
  UIButton::UIButton(Core::DisplayDriver *disp, UIButtonType buttonType): display(disp) {
    switch (buttonType)
    {
    case UIButtonType::BACK_BUTTON:
      this->width = 8;
      this->height = 10;
      break;

    default:
      break;
    }
  }

  void UIButton::render(bool isSelected) {
    // TODO: render button logic
  }
}