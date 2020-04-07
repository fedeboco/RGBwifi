#include "board.h"

board::board(int brate) : brate(brate), server(WiFiServer(80)), 
                          manualValue(0), currentColour(colour(0,0,0)),
                          manualSum(0), RGB(strip(12,13,14)), mode(WIFI_MODE),
                          modeButton(0){
  Serial.begin(115200); //baud rate
  WiFi.mode(WIFI_STA); //estacion
  WiFi.disconnect();
  delay(100);
  pinMode(2, OUTPUT);
  for(int i = 0; i < AVERAGE_LEN; i++) manualValues.push(0);
}

void board::printNetworks() {
  // number of available networks
  int n = WiFi.scanNetworks();
  if (n == 0) 
    Serial.println("No networks available.");

  // prints number of networks
  Serial.print("Number of networks available: ");
  Serial.println(n);

  /* prints names (SSID), signal intensity (RSSI)
  and encryption type. */
  for (int i = 0; i < n; i++) {
    Serial.print(i + 1);
    Serial.print(") ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (RSSI: ");
    Serial.print(WiFi.RSSI(i));
    Serial.print("). ");
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
  WiFi.begin(ssid, password);
  waitForConnection();
  Serial.print("\nConnected successfully to ");
  Serial.print(ssid);
  Serial.println(".");
  Serial.print("Device IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

// waits for clients
WiFiClient board::listen() {
    return server.available();
}

void board::serialWelcome() {
  Serial.print("\n\n");
  Serial.println("--------------------------");
  Serial.println("RGB WiFi Strip Controller.");
  Serial.println("--------------------------");
}

void board::waitForConnection() {
  bool ledOn = true;
  uint8_t counter = 0;

  digitalWrite(2, HIGH);
  while (WiFi.status() != WL_CONNECTED) { 
    counter++;
    if (counter > 3) {
      Serial.print(".");
      if (ledOn) {
        ledOn = false;
        digitalWrite(2, LOW);
      } else {
        ledOn = true;
        digitalWrite(2, HIGH);
      }
      counter = 0;
    }
    delay(50);
  }
  digitalWrite(2, LOW);
}

void board::updateManualControl() {
  if (mode != MANUAL_MODE) return;
  manualSum += manualValues.back();
  manualSum -= manualValues.front();
  manualValues.push(analogRead(A0) / 1023.0 / 0.88);
  manualValues.pop();
  currentColour.rainbow(manualSum / AVERAGE_LEN);
  RGB.setColour(currentColour);
}

void board::updateStrobe() {
  if (mode != STROBE_MODE) return;
  RGB.brightness(currentColour, analogRead(A0) / 1023.0 / 0.88);
  RGB.strobe(strobeIndex);
}

void board::updateBrightness() {
  if (mode != BRIGHTNESS_MODE) return;
  RGB.brightness(currentColour, analogRead(A0) / 1023.0 / 0.88);
}

void board::updateMode() {
  if (modeButton.isPressed()) {
    mode = (boardMode_t) (mode + 1);
    if (mode == DEFAULT_MODE) {
      mode = (boardMode_t) 0;
    } else if (mode == WIFI_MODE) {
      RGB.flash(FLASH_DELAY, colour(WHITE), FLASH_TIMES);
      RGB.setColour(colour(currentColour));
    } else if (mode == MANUAL_MODE) {
      RGB.flash(FLASH_DELAY, colour(WHITE), FLASH_TIMES);
      RGB.setColour(colour(currentColour));
    } else if (mode == STROBE_MODE) {
      RGB.flash(FLASH_DELAY, colour(WHITE), FLASH_TIMES);
    } else if (mode == BRIGHTNESS_MODE) {
      RGB.flash(FLASH_DELAY, colour(WHITE), FLASH_TIMES);
      RGB.setColour(colour(currentColour));
    }
  }

  Serial.println(mode);
}

