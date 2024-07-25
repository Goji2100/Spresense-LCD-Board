// -----------------------------------------------------------------------------
#if defined(USE_LovyanGFX)
void tftTPinit() {

  tft.begin();
  tft.setRotation(TFT_ROTATION);
  tft.fillScreen(TFT_BLACK);

  #if defined(USE_XPT2048)||defined(USE_STME610)
    TP.begin();
    #if defined(USE_XPT2048)
      TP.setRotation(1);
    #endif

    #if (0) // for ILI9486
      tft.drawBitmap(344, 144, ICON_heart  ,  36, 32, TFT_PINK);
      uint16_t px, py;
      while(!getTouch(&px, &py));
      if (px < tft.width() / 2) {
        tft.setRotation(5);
        tft.fillScreen(TFT_BLACK);
        tft.drawBitmap(344, 144, ICON_heart  ,  36, 32, TFT_PINK);
        while( getTouch(&px, &py));
        while(!getTouch(&px, &py));
      }
      tft.fillScreen(TFT_BLACK);
    #endif

    drawShutter(TFT_GREEN);
  
  #endif

  dispPictureSize(g_width, g_height);
  tft.fillRect(Z4_px, Z4_py, tft.width(), 2, TFT_DARKGREY);

}
#endif

#if defined(USE_XPT2048)||defined(USE_STME610)
void drawShutter(uint16_t color) {
  int sizeup = (Z3_px > 320) ? 4 : 0;

  tft.fillCircle(Z3_px + (Z3_pw / 2), 60, 22 + sizeup, color);
  tft.fillCircle(Z3_px + (Z3_pw / 2), 60, 20 + sizeup, TFT_BLACK);
  tft.fillCircle(Z3_px + (Z3_pw / 2), 60, 14 + sizeup, color);
}
#endif

#if defined(USE_LovyanGFX)||defined(USE_LIB_ADAFRUIT_ILI9341)
void displayFPS(size_t sw) {
  static volatile size_t loopCnt = 0;
  static uint64_t p_millis = millis();

  // Display Lap time
  loopCnt++;
  uint64_t lap_millis = (millis() - p_millis);

  if ((lap_millis >= 1000) && (sw == 0)) {
    float lap = ((float)lap_millis / loopCnt);
    float fps = (1000.0 / lap);
    drawFPS(fps);
    sw = 1;
  }

  if (sw == 1) {
    loopCnt = 0;
    p_millis = millis();
  }
}
#endif

// ---------------------------------------------------------
#if defined(USE_LovyanGFX)
void drawFPS(float fps) {
  char fpss[16];

  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  sprintf(fpss, (Z3_pw < 40) ? "%5.2f" : "%5.2ffps", fps);
  tft.drawCenterString(fpss,   Z3_px + (Z3_pw / 2), (Z3_ph / 2) + 20);
}

// ---------------------------------------------------------
void dispPictureSize(size_t dw, size_t dh) {
  char dwidth[32];

  sprintf(dwidth, "%dx%d", dw, dh);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRect(Z3_px, (Z3_ph / 2) + 36, Z3_pw, 8, TFT_BLACK);
  tft.drawCenterString(dwidth, Z3_px + (Z3_pw / 2), (Z3_ph / 2) + 36);
}

// ---------------------------------------------------------
#elif defined(USE_LIB_ADAFRUIT_ILI9341)
void drawFPS(float fps) {
  int x = (20 + 240 + (60 - (6 * 5)) / 2), y = 140 - (8 / 2);
  char fpss[16];

  sprintf(fpss, "%5.2f", fps);
  for (char *s = fpss; *s; s++, x+= 6) {
    tft.drawChar(x, y, *s, ILI9341_WHITE, ILI9341_BLACK, 1);
  }
}
#endif

// -----------------------------------------------------------------------------
#if defined(USE_LovyanGFX)
void makeThumb(CamImage *img, int g_pict_id) {
  static size_t spos = -1;
  char filename[32];

  #if defined(USE_ILI9486)||defined(USE_ILI9488)
  // Thumbnail
    #define THUMB_WW        ( 80)
    #define THUMB_HH        ( 60)
    #define Z4_tx           ((480 - (THUMB_WW + 4) * 5 - 4) / 2)

  #elif defined(USE_ILI9341)||defined(USE_ADAFRUIT_ILI9341)

  // Thumbnail
    #define THUMB_WW        ( 52)
    #define THUMB_HH        ( 40)
    #define Z4_tx           ((320 - (THUMB_WW + 4) * 5 - 4) / 2)
  #endif

  #define THUMB_POSX(n)     (Z4_tx + (n % 5) * (THUMB_WW + 4))
  #define THUMB_POSY()      (Z4_py + 4)

  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  if (spos >= 0)
    tft.drawRect(THUMB_POSX(spos++)    , THUMB_POSY()    , THUMB_WW + 2, THUMB_HH + 2, TFT_DARKGRAY );
  tft.drawRect  (THUMB_POSX(spos  )    , THUMB_POSY()    , THUMB_WW + 2, THUMB_HH + 2, TFT_LIGHTGREY);
  tft.fillRect  (THUMB_POSX(spos  ) + 1, THUMB_POSY() + 1, THUMB_WW    , THUMB_HH    , TFT_DARKGRAY );

  if (img->getPixFormat() == CAM_IMAGE_PIX_FMT_JPG) {  // JPEG format
    float zoomRatio;
    tft.setSwapBytes(true);
    if (((float)img->getWidth() / THUMB_WW) > ((float)img->getHeight() / THUMB_HH) )
      zoomRatio = ((float)THUMB_HH / img->getHeight());
    else
      zoomRatio = ((float)THUMB_WW / img->getWidth());
    int x = THUMB_POSX(spos) + 1, y = THUMB_POSY() + 1;
    tft.drawJpg(img->getImgBuff(), img->getImgSize(), x, y, THUMB_WW, THUMB_HH, 0, 0, zoomRatio, zoomRatio);
    tft.setSwapBytes(false);
  } else {
      tft.drawCenterString("X", THUMB_POSX(spos) + (THUMB_WW / 2), THUMB_POSY() + (THUMB_WW / 2));
  }

  sprintf(filename, "%04d.%s", g_pict_id,
        (img->getPixFormat() == CAM_IMAGE_PIX_FMT_RGB565) ? "RGB" :
        (img->getPixFormat() == CAM_IMAGE_PIX_FMT_YUV422) ? "YUV" :
        (img->getPixFormat() == CAM_IMAGE_PIX_FMT_JPG)    ? "JPG" :
        (img->getPixFormat() == CAM_IMAGE_PIX_FMT_GRAY)   ? "GRAY" : "NONE");
  tft.drawCenterString(filename, THUMB_POSX(spos) + (THUMB_WW / 2), THUMB_POSY() +  2);
}
#endif

// -----------------------------------------------------------------------------
#if defined(USE_XPT2048)||defined(USE_STME610)

#if defined(USE_XPT2048)
  uint16_t TPxMin = 190, TPxMax = 3660;
  uint16_t TPyMin = 350, TPyMax = 3600;
#elif defined(USE_STME610)
  uint16_t TPxMin = 250, TPxMax = 3600;
  uint16_t TPyMin = 200, TPyMax = 3800;
#endif

bool getTouch(uint16_t *px, uint16_t *py) {
  if (TP.touched()) {
    TS_Point p = TP.getPoint();
    if (p.z > 100 && p.x >= 0 && p.z <= 4095 && p.y >= 0 && p.y <= 4095) {
      //Serial.printf("x=%u,y=%u,z=%u (%u) ", p.x, p.y, p.z, TP_ROTATION);
      uint16_t x = p.x + 2, y = p.y + 2;
      if (TP_ROTATION & TPC_R) std::swap(x, y);
      if (TP_ROTATION & TPC_X) { x = 4095 - x; }
      if (TP_ROTATION & TPC_Y) { y = 4095 - y; }
      x = constrain(x, TPxMin, TPxMax);
      y = constrain(y, TPyMin, TPyMax);
      *px = map(x, TPxMin, TPxMax, 0, (tft.width()  - 1));
      *py = map(y, TPyMin, TPyMax, 0, (tft.height() - 1));
      //Serial.printf("x=%u,y=%u\n", *px, *py);
      return (true);
    } else 
      ;//Serial.printf("x=%d,y=%d,z=%d\n", p.x, p.y,p.z);
  } else return (false);
}

// ---------------------------------------------------------
bool getShutter() {
  uint16_t px, py;

  if (getTouch(&px, &py)) {
    if ( (px > Z3_px) && (py < (Z3_ph / 2)) ) {
      return(true);
    }
  }
  return(false);
}
#endif
