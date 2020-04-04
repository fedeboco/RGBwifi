#include "ESP8266WiFi.h"
#include "board.h"
#include "colour.h"
#include "strip.h"

#define FLASH_PERIOD 500 // ms

const char* ssid = "Network-Name";     // Aqui van vuestros datos
const char* password = "6#Z9K%L>e@7GdDtj";
WiFiServer server(80); //defino servidor
board WiFiBoard(115200);
strip RGB(12, 13, 14);
colour red(255, 0, 0);
colour pink(255, 50, 50);
colour green(0, 255, 0);
colour blue(0, 0, 255);
colour rain;
float rainIndex = 0;
int pote = 0;

void setup() {

  WiFiBoard.serialWelcome();
  WiFiBoard.printNetworks();
  WiFiBoard.connect(ssid, password);

}

void loop() {
  rainIndex += 0.002;
  if (rainIndex > 1)
    rainIndex = 0;
  rain.rainbow(rainIndex);
  RGB.setColour(rain);
  delay(15);


  
  /*RGB.setColour(red);
  delay(FLASH_PERIOD);
  RGB.setColour(green);
  delay(FLASH_PERIOD);
  RGB.setColour(blue);
  delay(FLASH_PERIOD);
  RGB.setColour(pink);
  delay(FLASH_PERIOD);*/
  

  
}
