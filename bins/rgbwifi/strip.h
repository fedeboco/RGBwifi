#ifndef STRIP_H
#define STRIP_H

#include <stdint.h>
#include "colour.h"
#include "ESP8266WiFi.h"

class strip {
  private:
    uint8_t Rpin;
    uint8_t Gpin;
    uint8_t Bpin;
    float brigthnessFactor;
    
  public:
    strip(uint8_t, uint8_t, uint8_t);
    void setColour(colour);
    void flash(int, colour, int);
    void strobe(colour &, float &);
    void brightness(colour &, float);
};

#endif
