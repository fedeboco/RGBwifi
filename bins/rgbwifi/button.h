#ifndef BUTTON_H
#define BUTTON_H

#include "ESP8266WiFi.h"

class button {
  private:
    bool holding = 0;
    bool released = 1;
    long unsigned holdStart;
    int pin;
  
  public:
    bool isPressed();
    button(int pin);
    bool beingHold();
    bool holded(unsigned long);
};


#endif
