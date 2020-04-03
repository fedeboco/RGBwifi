#ifndef BOARD_H
#define BOARD_H

#include "ESP8266WiFi.h"
#include <stdint.h>

class board {
  private:
  int brate;

  public:
  board(int);
  void printNetworks();
  void printEncryptionType(uint8_t);
  void connect(const char *, const char *);
  void serialWelcome();
};

#endif
