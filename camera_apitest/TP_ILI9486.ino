#ifdef USE_TP_ILI9486

uint16_t xMin = 190, xMax = 3660;
uint16_t yMin = 350, yMax = 3600;

bool getTouch(uint16_t *px, uint16_t *py) {
  uint16_t x, y;

  if (TP.touched()) {
    TS_Point p = TP.getPoint();
    x = constrain(p.x,          xMin, xMax);
    y = constrain((4095 - p.y), yMin, yMax);
    *px = map(x, xMin, xMax, 0, (480 - 1));
    *py = map(y, yMin, yMax, 0, (320 - 1));
    return (true);
  } else return (false);
}

void drawShutter(uint16_t color) {
  tft.fillCircle(440, 60, 24, color);
  tft.fillCircle(440, 60, 22, TFT_BLACK);
  tft.fillCircle(440, 60, 16, color);
}

void dispPictureSize(size_t w, size_t h) {
  char dwidth[32];

  tft.fillRect(400, 170, 80, 8, TFT_BLACK);
  sprintf(dwidth, "[%dx%d]", w, h);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawCenterString(dwidth, 440, 170);
}

#endif
