#pragma once
#include <LovyanGFX.hpp>

namespace Core {

  class DisplayDriver: public lgfx::LGFX_Device {
  public:
      DisplayDriver();
      void init();
      void homePage();
      void settingsPage();
      void showTime(const char *timeStr);

    private:
      lgfx::Panel_ST7789 _panel;
      lgfx::Bus_SPI _bus;
      lgfx::LGFX_Sprite spriteClock;
      lgfx::LGFX_Sprite spriteMenu;
      lgfx::LGFX_Sprite spriteNotif;
  };
}
