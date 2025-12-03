#include "../core/DisplayDriver.hpp"

namespace Ui {
  enum class UIButtonType {
    BACK_BUTTON,
  };

  class UIButton {
    public:
      UIButton(Core::DisplayDriver *disp, UIButtonType type);
      void render(bool isSelected);
    private:
      Core::DisplayDriver *display;
      uint32_t width;
      uint32_t height;
      uint32_t x;
      uint32_t y;
  };
}