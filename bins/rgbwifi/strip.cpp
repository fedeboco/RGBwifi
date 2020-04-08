#include "strip.h"

strip::strip(uint8_t Rpin, uint8_t Gpin, uint8_t Bpin) : Rpin(Rpin), Gpin(Gpin), Bpin(Bpin) {
    pinMode(Rpin, OUTPUT);
    pinMode(Gpin, OUTPUT);
    pinMode(Bpin, OUTPUT);
}

void strip::setColor(color color) {
    analogWrite(Rpin, color.getR() * 1023 / 255 * brightnessFactor);
    analogWrite(Gpin, color.getG() * 1023 / 255 * brightnessFactor);
    analogWrite(Bpin, color.getB() * 1023 / 255 * brightnessFactor);
}

void strip::flash(int period, color c, int times) {
    for(int i = 0; i < times; i++) {
      setColor(c);
      delay(period);
      setColor(color(0,0,0));
      delay(period);
    }
}

void strip::strobe(color & current, float & index) {
  index += 0.002;
  if (index > 1) index = 0;
  current.rainbow(index);
  delay(25);
}

void strip::setBrightness(float factor) {
  if (factor > 0.65) factor = 0.65;
  factor = factor * 2 - 0.3;
  if (factor < 0) factor = 0;
  brightnessFactor = factor;
}

