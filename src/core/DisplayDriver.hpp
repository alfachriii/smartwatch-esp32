#pragma once
#include <LovyanGFX.hpp>

namespace Core {

  class DisplayDriver : public lgfx::LGFX_Device {
  public:
      DisplayDriver();
      void init();
      void showTime(const char* timeStr);
      void homePage(const char *timeStr);
  
    private:
      lgfx::Panel_ST7789 _panel;
      lgfx::Bus_SPI _bus;
      lgfx::LGFX_Sprite spriteClock;
      lgfx::LGFX_Sprite spriteMenu;
      lgfx::LGFX_Sprite spriteNotif;
  };
}
