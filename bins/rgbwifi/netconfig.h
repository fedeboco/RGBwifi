#ifndef NETCONFIG_H
#define NETCONFIG_h

#include "ESP8266WiFi.h"

class netConfig {
    private:
    WiFiServer server;
    WiFiClient client;
    
    public:
    netConfig();
    ~netConfig();
    void updateCredentials();
    void sendWebPage();
    void serverStop();
};

#endif
