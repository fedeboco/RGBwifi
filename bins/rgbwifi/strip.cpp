#include "strip.h"

strip::strip(uint8_t Rpin, uint8_t Gpin, uint8_t Bpin) : Rpin(Rpin), Gpin(Gpin), Bpin(Bpin) {
    pinMode(Rpin, OUTPUT);
    pinMode(Gpin, OUTPUT);
    pinMode(Bpin, OUTPUT);
}

void strip::setColour(colour colour) {
    analogWrite(Rpin, colour.getR() * 1023 / 255);
    analogWrite(Gpin, colour.getG() * 1023 / 255);
    analogWrite(Bpin, colour.getB() * 1023 / 255);
}

void strip::flash(int period, colour c, int times) {
    for(int i = 0; i < times; i++) {
      setColour(c);
      delay(period);
      setColour(colour(0,0,0));
      delay(period);
    }
}

void strip::strobe(colour & current, float & index) {
  index += 0.002;
  if (index > 1) index = 0;
  current.rainbow(index);
  brightness(current, brigthnessFactor);
  delay(25);
}

void strip::brightness(colour & current, float factor) {
  uint8_t R = current.getR();
  uint8_t G = current.getG();
  uint8_t B = current.getB();
  uint8_t maxColor = R;
  if (G > maxColor)
    maxColor = G;
  if (B > maxColor) 
    maxColor = B;
  R = 255.0 * R / maxColor * factor;
  G = 255.0 * G / maxColor * factor;
  B = 255.0 * B / maxColor * factor;
  /*current.recolor(R,G,B);*/ //DESCOMENTAR PARA BRILLO
  brigthnessFactor = factor;
}

