#include "board.h"

typedef enum {
    TKIP_WPA = 2,
    WEP = 5,
    CCMP_WPA = 4,
    NONE = 7,
    AUTO = 8
} encryption_t;

board::board(int brate) : brate(brate) {
  Serial.begin(115200); //baud rate
  WiFi.mode(WIFI_STA); //estacion
  WiFi.disconnect();
  delay(100);
}

void board::printNetworks() {
  // number of available networks
  int n = WiFi.scanNetworks();
  if (n == 0) 
    Serial.println("No networks available.");

  // prints number of networks
  Serial.print(n);
  Serial.println(" networks found:");

  /* prints names (SSID), signal intensity (RSSI)
  and encryption type. */
  for (int i = 0; i < n; i++) {
    Serial.print(i + 1);
    Serial.print("| ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (RSSI: ");
    Serial.print(WiFi.RSSI(i));
    Serial.print(") - ");
    printEncryptionType(WiFi.encryptionType(i));
    delay(50);
  }
}

void board::printEncryptionType(uint8_t enc) {
    if (enc == TKIP_WPA) Serial.println("WPA (TKIP)");
    else if (enc == CCMP_WPA) Serial.println("WPA (CCMP)");
    else if (enc == WEP) Serial.println("WEP");
    else if (enc == ENC_TYPE_NONE) Serial.println("Open network");
    else if (enc == AUTO) Serial.println("Auto");
    else Serial.println("Unknown encryption");
}

void board::connect(const char * ssid, const char * password) {
  uint8_t counter = 0;

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    counter++;
    if (counter > 3) {
      Serial.print("\b\b\b");
      counter = 0;
    }
    delay(250);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}
