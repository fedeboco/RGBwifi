#ifndef BOARD_H
#define BOARD_H

#include "ESP8266WiFi.h"
#include <stdint.h>
#include <queue>
#include "colour.h"
#include "strip.h"
#include "button.h"

#define AVERAGE_LEN 50.0
#define WHITE 255,255,255
#define FLASH_DELAY 100 //ms
#define FLASH_TIMES 4

typedef enum {
    TKIP_WPA = 2,
    WEP = 5,
    CCMP_WPA = 4,
    NONE = 7,
    AUTO = 8
} encryption_t;

typedef enum {
  WIFI_MODE = 0,
  MANUAL_MODE = 1,
  BRIGHTNESS_MODE = 2,
  STROBE_MODE = 3,
  DEFAULT_MODE
} boardMode_t;

class board {
  private:
  int brate;
  WiFiServer server;
  float manualValue;
  float manualSum;
  std::queue<float> manualValues;
  colour currentColour;
  float strobeIndex = 0;
  strip RGB;
  boardMode_t mode;
  button modeButton;
  float brightness;
    
  public:
  board(int);
  WiFiClient listen();
  void printNetworks();
  void printEncryptionType(uint8_t);
  void connect(const char *, const char *);
  void serialWelcome();
  void waitForConnection();
  void updateManualControl();
  void updateMode();
  void updateStrobe();
  void updateBrightness();
  
};

#endif
