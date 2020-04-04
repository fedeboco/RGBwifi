#include "strip.h"

strip::strip(uint8_t Rpin, uint8_t Gpin, uint8_t Bpin) : Rpin(Rpin), Gpin(Gpin), Bpin(Bpin) {
    pinMode(Rpin, OUTPUT);
    pinMode(Gpin, OUTPUT);
    pinMode(Bpin, OUTPUT);
}

void strip::setColour(colour colour) {
    analogWrite(Rpin, colour.getR());
    analogWrite(Gpin, colour.getG());
    analogWrite(Bpin, colour.getB());
}
