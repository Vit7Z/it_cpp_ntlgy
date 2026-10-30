#ifndef lib_a4988_h
#define lib_a4988_h
#include "Arduino.h"
 
class A4988
{
  public:
    A4988(const uint8_t stepPin, const uint8_t dirPin);
    void Rotate(void);
    void SetSpeed(int s);
    void SetSteps(int s);
    void Direction(bool d);

  private:
    int dir_pin_; //вывод для направления
    int step_pin_; //вывод для шага
    int speed_;
    int steps_;
};
 
#endif