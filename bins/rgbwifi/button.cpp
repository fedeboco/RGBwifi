#include "button.h"

button::button(int pin) : holding(0), released(1), pin(pin) {
    pinMode(pin, INPUT_PULLUP);
}

// Returns true only if button goes OFF->ON. INTERNAL PULL UP ON.
bool button::isPressed() {
  if (released && digitalRead(pin) == LOW){
    released = 0;
    holding = 1;
    return true; // first press
  } else if (released == 0 && digitalRead(pin) == LOW) {
    return false; // holding
  } else if (holding == 1 && digitalRead(pin) == HIGH) {
    released = 1;
    holding = 0;
    return false; // released
  }
}

bool button::beingHold() {
  return holding;
}

