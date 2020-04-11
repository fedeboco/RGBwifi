#ifndef BOARD_H
#define BOARD_H

#include "ESP8266WiFi.h"
#include <stdint.h>
#include <queue>
#include "color.h"
#include "strip.h"
#include "button.h"
#include "htmlclient.h"
#include "netconfig.h"
#include "EEPROM.h"

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
  float scaleValue;
  float scaleSum;
  std::queue<float> scaleValues;
  color currentColor;
  color WiFiCurrentColor;
  float strobeIndex = 0;
  strip RGB;
  boardMode_t mode;
  button modeButton;
  float brightness;
  htmlClient RGBClient;
    
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
  void updateWiFiClient(); 
  void updateColor();
  void updateAnalogScale();
  void blinkStatusLed(uint8_t);
  void startAccessPointMode();
  void startStationMode();
  String loadCredential(int start, int end);
};

#endif
