#pragma once

#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9486 _panel_instance;
  lgfx::Bus_SPI       _bus_instance;

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();
      cfg.freq_write = 40000000;
      cfg.pin_sclk = TFT_SCLK;      // SPIのSCLKピン番号を設定
      cfg.pin_mosi = TFT_MOSI;      // SPIのMOSIピン番号を設定
      cfg.pin_miso = TFT_MISO;      // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc   = TFT_DC;        // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }
    {
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。
      cfg.pin_cs         =  TFT_CS; // CSが接続されているピン番号   (-1 = disable)
      cfg.dlen_16bit     =  true;   // データ長を16bit単位で送信するパネルの場合 trueに設定
      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);     // 使用するパネルをセットします。
  }
};
