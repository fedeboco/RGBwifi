#ifndef STRIP_H
#define STRIP_H

#include <stdint.h>
#include "color.h"
#include "ESP8266WiFi.h"

class strip {
  private:
    uint8_t Rpin;
    uint8_t Gpin;
    uint8_t Bpin;
    float brigthnessFactor;
    
  public:
    strip(uint8_t, uint8_t, uint8_t);
    void setColor(color);
    void flash(int, color, int);
    void strobe(color &, float &);
    void brightness(color &, float);
};

#endif
