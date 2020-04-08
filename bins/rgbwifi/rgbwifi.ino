#include "ESP8266WiFi.h"
#include "board.h"
#include "colour.h"
#include "strip.h"

#define FLASH_PERIOD 500 // ms

const char* ssid = "test";
const char* password = "test";
board WiFiBoard(115200);

void setup() {
  WiFiBoard.serialWelcome();
  WiFiBoard.printNetworks();
  WiFiBoard.connect(ssid, password);
}

void loop() {
  WiFiBoard.updateMode();
  WiFiBoard.updateManualControl();
  WiFiBoard.updateStrobe();
  WiFiBoard.updateBrightness();
  WiFiBoard.updateWiFiClient();
  WiFiBoard.updateColour();
}
