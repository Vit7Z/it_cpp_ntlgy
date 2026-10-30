#include "lib_a4988.h"

const int dirPin {2}; //direction
const int stepPin {3}; //steps

A4988 a4988(stepPin, dirPin);

void setup() {
  a4988.SetSteps(200);
  Serial.begin(9600);
}

void loop() {
  
  a4988.SetSpeed(2000);
  a4988.Direction(0);
  a4988.Rotate();
  delay(1000);

  a4988.SetSpeed(1000);
  a4988.Direction(1);
  a4988.Rotate();
  delay(1000);
  }