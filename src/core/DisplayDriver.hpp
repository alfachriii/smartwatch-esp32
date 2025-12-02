#pragma once
#include <LovyanGFX.hpp>

namespace Core {

  class DisplayDriver: public lgfx::LGFX_Device {
  public:
      DisplayDriver();
      void init();

    private:
      lgfx::Panel_ST7789 _panel;
      lgfx::Bus_SPI _bus;
  };
}
