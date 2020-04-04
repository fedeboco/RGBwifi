#include "colour.h"

colour::colour() : R(0), G(0), B(0) {}

colour::colour(uint8_t R, uint8_t G, uint8_t B) : R(R), G(G), B(B) {}

uint8_t colour::getR() {
  return R; 
}

uint8_t colour::getG() {
  return G; 
}

uint8_t colour::getB() {
  return B; 
}

float colour::redRainbow(float pos) {
  if (pos < 1.0/6 || pos > 5.0/6) {
    return 1;
  } else if (pos >= 1.0/6 && pos < 2.0/6) {
    return -6.0 * pos + 2.0;
  } else if (pos > 4.0/6 && pos <= 5.0/6) {
    return 6.0 * pos - 4.0;
  } else {
    return 0;
  }
}

float colour::greenRainbow(float pos) {
  if (pos < 3.0/6 && pos > 1.0/6) {
    return 1;
  } else if (pos > 0 && pos <= 1.0/6) {
    return 6.0 * pos;
  } else if (pos >= 3.0/6 && pos < 4.0/6) {
    return -6.0 * pos + 4.0;
  } else {
    return 0;
  }
}

float colour::blueRainbow(float pos) {
  if (pos < 5.0/6 && pos > 3.0/6) {
    return 1;
  } else if (pos >= 2.0/6 && pos < 3.0/6) {
    return 6.0 * pos - 2.0;
  } else if (pos >= 5.0/6 && pos <= 1) {
    return -6.0 * pos + 6.0;
  } else {
    return 0;
  }
}

void colour::rainbow(float pos) {
  R = redRainbow(pos) * 255;
  G = greenRainbow(pos) * 255;
  B = blueRainbow(pos) * 255;
}

