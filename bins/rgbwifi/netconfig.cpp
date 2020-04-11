#include "netConfig.h"

netConfig::netConfig() {
    WiFi.softAP("RGB-C");
    Serial.print("Configuration IP: ");
    Serial.println(WiFi.softAPIP());
    updated = false;
    server.on("/config-sent", std::bind(&netConfig::handleConfigSent, this));
    server.on("/", std::bind(&netConfig::handleRootAddress, this));
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
  while(!updated)  {
    server.handleClient();
    delay(100);
  }
}

void netConfig::handleConfigSent() {
  Serial.print("Received user and password");
  String user = server.arg("user");
  String pass = server.arg("pass");
  if (user.length() > 128 || pass.length() > 128) return;
  WiFi.begin(user, pass);
  digitalWrite(2, HIGH);
  unsigned long timer = millis();
  bool disconnected = true;
  uint8_t counter = 0;
  bool ledOn = false;
  while (disconnected && millis() - timer < 10000) { 
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
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("CONNECTED");
      updated = true;
      disconnected = false;
      saveCredentials(user, pass);
    }
  }
}

void netConfig::saveCredentials(String user, String pass) {
  EEPROM.begin(512);
  delay(10);
  for (int i=0; i < user.length(); i++) {
    EEPROM.write(0 + i, user[i]);
    Serial.print(user[i]);
  }
  EEPROM.write(user.length(), '\n');
  for (int i=0; i < pass.length(); i++) {
    EEPROM.write(128 + i, pass[i]);
    Serial.print(pass[i]);
  }
  EEPROM.write(128 + pass.length(), '\n');
  EEPROM.commit();
  Serial.println(""); 
}

String netConfig::getWiFiConnectedMessage() {
  return  "<!DOCTYPE html>"
          "<html>"
          "<title> RGB-C Configuration </title>" 
          "<style>"
          "body {"
          "font-family: 'Lucida Sans Unicode', 'Arial Narrow Bold', sans-serif;"
          "text-align: center;"
          "}"
          "</style>"
          
          "<h1>Wi-Fi Connected.</h1>"
          "</html>";
}

void netConfig::handleRootAddress() {

  String web = "<!DOCTYPE html>="
  "<html>"
  "<head>"
  "<title> RGB-C Configuration </title>"
  "<style>"
  "h1 {"
  "font-family: 'Lucida Sans Unicode', 'Arial Narrow Bold', sans-serif;"
  "}"
  "h2{"
  "font-family: 'Lucida Sans Unicode', 'Arial Narrow Bold', sans-serif;"
  "font-size: 15px;"
  "}"
  "h3{"
  "font-family: 'Lucida Sans Unicode', 'Arial Narrow Bold', sans-serif;"
  "font-size: 11px;"
  "}"
  "body {"
  "text-align: center;"
  "}"
  ".grid-container {"
  "display: grid;"
  "grid-template-columns: auto 80px 80px 110px auto;"
  "text-align: right;"
  "align-self: center;"
  "}"
  ".grid-container > div {"
  "text-align: center;"
  "padding: 20px 0;"
  "font-size: 15px;"
  "}"
  "</style>"
  "</head>"

  "<body>"
  "<h1>RGB WiFi Controller</h1>"
  "<br> <h2>WiFi Network Settings</h2>"
  "<br > <h3>Your device will connect to this network.</h3>"
  "<form action='config-sent' method='post'>"
  "<div class=\"grid-container\">"
  "<div></div>"
  "<div>Network Name</div>"
  "<div > <input type=\"text\" name=\"user\" required> </div>"
  "<div></div>"
  "<div></div>"
  "<div></div>"
  "<div>Password</div>"
  "<div> <input type=\"password\" name=\"pass\"> </div>"
  "<div></div>"
  "<div></div>"
  "</div>"
  "<input type=\"submit\">"
  "</form>"
  "</body>"

  "</html>";
  
  server.send(200, "text/html", web);
}
