#include "DisplayDriver.hpp"
#include "config.h"


namespace Core {

  DisplayDriver::DisplayDriver(){
      {
          auto cfg = _bus.config();
          cfg.spi_host = SPI2_HOST;
          cfg.spi_mode = TFT_SPI_MODE;
          cfg.freq_write = 40000000;
          cfg.freq_read  = 16000000;
          cfg.pin_sclk = TFT_SCK_PIN;   
          cfg.pin_mosi = TFT_MOSI_PIN;
          cfg.pin_miso = TFT_MISO_PIN;
          cfg.pin_dc   = TFT_DC_PIN;
          _bus.config(cfg);
          _panel.setBus(&_bus);
      }
  
      {
          auto cfg = _panel.config();
          cfg.pin_cs = TFT_CS_PIN;
          cfg.pin_rst = TFT_RST_PIN;
          cfg.pin_busy = -1;
          cfg.memory_width  = 240;
          cfg.memory_height = 240;
          cfg.panel_width   = 240;
          cfg.panel_height  = 240;
          cfg.offset_x = 0;
          cfg.offset_y = 0;
          cfg.offset_rotation = 0;
          cfg.invert = true;
          cfg.rgb_order = true;
          _panel.config(cfg);
      }
  
      setPanel(&_panel);
  }
  
  void DisplayDriver::init() {
      lgfx::LGFX_Device::init();
      setRotation(0);
      fillScreen(TFT_BLACK);
      setTextColor(TFT_WHITE, TFT_BLACK);
      setTextSize(2);
      drawString("Smartwatch Booting...", 10, 110);
  }

  void DisplayDriver::renderStatusBar(char *timeBuf, float &battPercent) {
    // TODO: RENDER TIME, RENDER BATT INDICATOR
  }
}
