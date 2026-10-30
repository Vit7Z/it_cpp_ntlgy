#ifndef LedRGB_h
#define LedRGB_h
#include "Arduino.h"

class LedRgb {
public:
    uint8_t brightR_;
    uint8_t brightG_;
    uint8_t brightB_;

    LedRgb(uint8_t pinR, uint8_t pinG, uint8_t pinB);
	
    uint8_t checkBright(uint8_t& bright, int8_t diff);
    void setColor(uint8_t val_1, uint8_t val_2, uint8_t val_3);
   // void setColorG(int8_t diff);
   // void setColorB(int8_t diff); 
   // void setMode(uint8_t value);
    void blink(uint16_t value);
private:
    uint8_t pinR_, pinG_, pinB_;
};

#endif // !LedRGB_h