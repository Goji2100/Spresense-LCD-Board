#pragma once

#include <Arduino.h>
#include <SPI.h>

#define USE_LovyanGFX

#define LCD_SPI       cfg.spi_port = 4
#define TFT_MOSI      11
#define TFT_MISO      12
#define TFT_SCLK      13
#define TFT_DC         9
#define TFT_RST       -1

#if defined(USE_ADAFRUIT_ILI9341)
  #define TFT_CS       6   // Requires hardware modifications (pin 10 -> pin 6)
#else
  #define TFT_CS       8
#endif

#define TPC_R          1    // TPC_ROTATE : swap(x, y)
#define TPC_X          2    // INVERT_X : x = -x
#define TPC_Y          4    // INVERT_Y : y = -y

#if defined(USE_ILI9341)||defined(USE_ADAFRUIT_ILI9341)
#if defined(USE_ADAFRUIT_ILI9341)
  #define TFT_ROTATION  3
  #define  TP_ROTATION ((TFT_ROTATION == 1) ? (TPC_R | TPC_X) : (TPC_R | TPC_Y))
#else
  #define TFT_ROTATION  3
  #define  TP_ROTATION ((TFT_ROTATION == 1) ? (            0) : (TPC_X | TPC_Y))
#endif
  #define Z2_px     ( 20)
  #define Z2_py     (  4)
  #define Z2_pw     (240)
  #define Z2_ph     (180)
  #define Z3_px     (260)
  #define Z3_pw     ( 60)
  #define Z3_ph     (190)
  #define Z4_px     (  0)
  #define Z4_py     (190)

#elif defined(USE_ILI9486)
  #define TFT_ROTATION 3
  #define  TP_ROTATION ((TFT_ROTATION == 1) ? (        TPC_X) : (        TPC_Y))
  #define Z2_px     ( 80)
  #define Z2_py     (  5)
  #define Z2_pw     (320)
  #define Z2_ph     (240)
  #define Z3_px     (400)
  #define Z3_pw     ( 80)
  #define Z3_ph     (250)
  #define Z4_px     (  0)
  #define Z4_py     (250)

#elif defined(USE_ILI9488)
  #define TFT_ROTATION 1
  #define  TP_ROTATION ((TFT_ROTATION == 1) ? (TPC_X | TPC_Y) : (            0))
  #define Z2_px     ( 80)
  #define Z2_py     (  5)
  #define Z2_pw     (320)
  #define Z2_ph     (240)
  #define Z3_px     (400)
  #define Z3_pw     ( 80)
  #define Z3_ph     (250)
  #define Z4_px     (  0)
  #define Z4_py     (250)

#endif // defined(USE_ILI9341)||defined(USE_ADAFRUIT_ILI9341)

#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Bus_SPI       _bus_instance;

  #if defined(USE_ILI9341)||defined(USE_ADAFRUIT_ILI9341)
  lgfx::Panel_ILI9341 _panel_instance;
  #elif defined(USE_ILI9486)
  lgfx::Panel_ILI9486 _panel_instance;
  #elif defined(USE_ILI9488)
  lgfx::Panel_ILI9488 _panel_instance;
  #else
  #error LCD
  #endif

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();

      LCD_SPI;
      #if defined(USE_ILI9486)
        cfg.freq_write  = 40000000;
      #elif defined(USE_ADAFRUIT_ILI9341)
        cfg.freq_write  = 36000000;
      #else
        cfg.freq_write  = 40000000;
      #endif
      cfg.pin_sclk      = TFT_SCLK;   // SPIのSCLKピン番号を設定
      cfg.pin_mosi      = TFT_MOSI;   // SPIのMOSIピン番号を設定
      cfg.pin_miso      = TFT_MISO;   // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc        = TFT_DC;     // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);      // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }
    {
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

      cfg.pin_cs        =  TFT_CS;    // CSが接続されているピン番号   (-1 = disable)
      #if defined(USE_ILI9486)
        cfg.dlen_16bit  =  true;      // データ長を16bit単位で送信するパネルの場合 trueに設定
      #endif
      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);     // 使用するパネルをセットします。
  }
};

LGFX tft;

#if defined(USE_STME610)

  #define TP_CS       8
  #include <Adafruit_STMPE610.h>
  Adafruit_STMPE610 TP = Adafruit_STMPE610(TP_CS, &SPI4);

#elif defined(USE_XPT2048)
  #define TP_CS       7
  #include <XPT2046_Touchscreen.h>
  XPT2046_Touchscreen TP(TP_CS);

#endif

