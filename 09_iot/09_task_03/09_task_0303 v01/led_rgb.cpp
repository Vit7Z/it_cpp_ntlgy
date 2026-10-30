#include "led_rgb.h"

LedRgb::LedRgb (uint8_t pinR, uint8_t pinG, uint8_t pinB) {
  pinR_ = pinR;
  pinG_ = pinG;
  pinB_ = pinB;

  brightR_ = 0;
  brightG_ = 0;
  brightB_ = 0;

  pinMode(pinR_, OUTPUT);
  pinMode(pinG_, OUTPUT);
  pinMode(pinB_, OUTPUT);
}

uint8_t LedRgb::checkBright (uint8_t& bright, int8_t diff) {
  if (diff < 0) {
    if (bright == 0) {
      bright = 0;
    } else {
      bright = bright + diff;
    }
  }

  if (diff > 0) {
    if (bright == 255) {
      bright = 255;
    } else {
      bright = bright + diff;
    }
  }
  return bright;
}

void LedRgb::setColor (uint8_t val_1, uint8_t val_2, uint8_t val_3) {
  brightR_ = val_1;
  brightG_ = val_2;
  brightB_ = val_3;

  analogWrite(pinR_, brightR_);
  analogWrite(pinG_, brightG_);
  analogWrite(pinB_, brightB_);
}

/*
  void LedRgb::setColorG (int8_t diff) {
  brightG_ = checkBright(brightG_, diff);

  }

  void LedRgb::setColorB (int8_t diff) {
  brightB_ = checkBright(brightB_, diff);

  }

  void LedRgb::setMode(uint8_t value) {
  analogWrite(pinR_, value);
  analogWrite(pinG_, value);
  analogWrite(pinB_, value);
  }
*/

void LedRgb::blink(uint16_t value) {
  analogWrite(pinR_, brightR_);
  analogWrite(pinG_, brightG_);
  analogWrite(pinB_, brightB_);
  delay(value);
  analogWrite(pinR_, 0);
  analogWrite(pinG_, 0);
  analogWrite(pinB_, 0);
  delay(value);
}