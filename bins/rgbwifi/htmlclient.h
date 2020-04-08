#ifndef HTML_CLIENT_H
#define HTML_CLIENT_H

#include "ESP8266WiFi.h"

class htmlClient {
    private:
    WiFiClient cl;
    unsigned long currentTime;
    unsigned long previousTime;
    long timeoutTime;
      
    public:
    bool isConnected();
    void listen(WiFiServer &);
    void stop();
    bool available();
    String process(String);
    WiFiClient getClient();
    htmlClient();
    void sendWebPage();
};

#endif
