#include "netConfig.h"

netConfig::netConfig() : server(WiFiServer(80)) {
    WiFi.softAP("RGB-C");
    Serial.println(WiFi.softAPIP());
    server.begin();
    updateCredentials();
}

void netConfig::updateCredentials() {
    bool updated = false;
    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    long timeoutTime = 200;
    client = server.available();
    while (!updated) {
      String request = "";
      if (client) {
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New Client.");
        String currentLine = "";
        while (client.connected() && currentTime - previousTime <= timeoutTime) {
          currentTime = millis();
          if (client.available()) {
            char c = client.read();
            Serial.write(c);
            request += c;
            if (c == '\n') {
              if (currentLine.length() == 0) {
                sendWebPage();
                updated = true;
                WiFi.disconnect();
              } else {
                currentLine = "";
              }
            } else if (c != '\r') {
              currentLine += c;
            }
          }
        }
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
      }
      delay(10);
    }
}

void netConfig::sendWebPage() {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
         
  client.println("test");
  client.println(); //ends html request
}
