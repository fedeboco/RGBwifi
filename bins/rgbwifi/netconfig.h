#ifndef NETCONFIG_H
#define NETCONFIG_h

#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
#include <functional>

class netConfig {
    private:
    ESP8266WebServer server = {80};
    WiFiClient client;
    bool updated = false;
    
    public:
    netConfig();
    ~netConfig();
    void updateCredentials();
    void serverStop();
    void handleConfigSent();
    void handleRootAddress();
    String getWiFiConnectedMessage();
};

#endif
