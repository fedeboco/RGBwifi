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
