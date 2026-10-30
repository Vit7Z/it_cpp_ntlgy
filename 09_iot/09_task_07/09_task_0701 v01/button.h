#ifndef Button_h
#define Button_h
#include "Arduino.h"

//----------------------------------------------
class Button {
  public:
    Button (uint8_t pin);

    void begin();
    bool wasPressed();
    
  private:
    uint8_t pin_;
    unsigned long debounce_time_;
    const unsigned long delay_ {20};
    bool last_state_;
};

#endif