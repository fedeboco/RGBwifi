#include "color.h"

color::color() : R(0), G(0), B(0) {}

color::color(uint8_t R, uint8_t G, uint8_t B) : R(R), G(G), B(B) {}

void color::recolor(int R, int G, int B) {
  this->R = R;
  this->G = G;
  this->B = B;
}

uint8_t color::getR() {
  return R; 
}

uint8_t color::getG() {
  return G; 
}

uint8_t color::getB() {
  return B; 
}

float color::redRainbow(float pos) {
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

float color::greenRainbow(float pos) {
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

float color::blueRainbow(float pos) {
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

void color::rainbow(float pos) {
  R = redRainbow(pos) * 255;
  G = greenRainbow(pos) * 255;
  B = blueRainbow(pos) * 255;
}

