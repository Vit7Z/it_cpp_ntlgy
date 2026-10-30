#include "lib_a4988.h"
#include "Arduino.h"

A4988::A4988(const uint8_t step_pin, const uint8_t dir_pin) {
  dir_pin_ = dir_pin;
  step_pin_ = step_pin;
  pinMode(step_pin_, OUTPUT);
  pinMode(dir_pin_, OUTPUT);
}

void A4988::Rotate(void) {
  for(int x = 0; x < steps_; x++) // медленный поворот двигателя
  {
    digitalWrite(step_pin_, HIGH);
    delayMicroseconds(speed_);
    digitalWrite(step_pin_, LOW);
    delayMicroseconds(speed_);
  }
}

void A4988::SetSpeed(int s) {
  speed_ = s;
}

void A4988::SetSteps(int s) {
  steps_ = s;
}

void A4988::Direction(bool d) {
  switch(d) {
  case false:
    digitalWrite(dir_pin_, HIGH); //установка направления
    break;
  case true:
    digitalWrite(dir_pin_, LOW); //противоположное направление
    break;
  }
}