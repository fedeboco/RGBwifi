#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

class colour {
  private:
    uint8_t R;
    uint8_t G;
    uint8_t B;
  
  public:
    colour(uint8_t R, uint8_t G, uint8_t B);
    void recolor(int R, int G, int B);
    colour();
    uint8_t getR();
    uint8_t getG();
    uint8_t getB();
    float blueRainbow(float);
    float redRainbow(float);
    float greenRainbow(float);
    void rainbow(float);

};


#endif
