#include "button.h"

Button::Button (uint8_t pin):
  pin_(pin), last_state_(0), debounce_time_(0) {
}

void Button::begin() {
  pinMode(pin_, INPUT_PULLUP);
  last_state_ = !digitalRead(pin_);
}

bool Button::wasPressed() {
  bool crnt_state_ = !digitalRead(pin_);
  bool flag_pressed = 0;

  if ((millis() - debounce_time_) > delay_) {
    if (crnt_state_ != last_state_ && last_state_ == 0) {
      flag_pressed = 1;
    }
    debounce_time_ = millis();
    last_state_ = !digitalRead(pin_);
  }
  return flag_pressed;
}