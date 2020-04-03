#include "ESP8266WiFi.h"
#include "board.h"

const char* ssid = "Network-Name";     // Aqui van vuestros datos
const char* password = "6#Z9K%L>e@7GdDtj";
WiFiServer server(80); //defino servidor
board WiFiBoard(115200);

void setup() {

  WiFiBoard.serialWelcome();
  WiFiBoard.printNetworks();
  WiFiBoard.connect(ssid, password);

}

void loop() {

}
