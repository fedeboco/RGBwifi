#include "ESP8266WiFi.h"
#include "board.h"

const char* ssid = "Network-Name";
const char* password = "6#Z9K%L>e@7GdDtj";
board WiFiBoard(115200);

void setup() {
  WiFiBoard.serialWelcome();
  WiFiBoard.printNetworks();
  WiFiBoard.connect(ssid, password);
}

void loop() {
  WiFiBoard.updateMode();
  WiFiBoard.updateAnalogScale();
  WiFiBoard.updateManualControl();
  WiFiBoard.updateStrobe();
  WiFiBoard.updateBrightness();
  WiFiBoard.updateWiFiClient();
  WiFiBoard.updateColor();
  WiFiBoard.startAccessPointMode();
}
