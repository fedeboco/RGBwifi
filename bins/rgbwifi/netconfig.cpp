#include "netConfig.h"

netConfig::netConfig() : server(WiFiServer(80)) {
    WiFi.softAP("RGB-C");
    Serial.print("Configuration IP: ");
    Serial.println(WiFi.softAPIP());
    server.begin();
}

netConfig::~netConfig() {
  server.stop();
  WiFi.softAPdisconnect();
}

void netConfig::serverStop() {
  server.stop();
}

void netConfig::updateCredentials() {
    bool updated = false;
    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    long timeoutTime = 200;
    while (!updated) {
      client = server.available();
      String request = "";
      Serial.print("A: ");
      Serial.println(client);
      if (client) {
        Serial.println("B");
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
      delay(1000);
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
