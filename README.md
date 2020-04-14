# ESP 8266 Wi-Fi RGB LED Strip Controller

![alt text](https://github.com/fedeboco/RGBwifi/blob/master/bins/board/rgbcontroller/circuit.png?raw=true)

### Idea
- Local network WiFi server.
- Browser GUI for color selection.
- Analog on-board hue-color and brightness selection.
- Multiple board control (not implemented yet).

### WiFi Configuration Example

Connecting to an specific Wi-Fi network will be possible by fisrt connecting to an Access Point created by the ESP and sending the credentials using that network. The device stores the settings in EEPROM and restarts with the desired network configured.

![alt text](https://github.com/fedeboco/RGBwifi/blob/master/bins/web/config_example.png?raw=true)

### Use Example

![alt text](https://github.com/fedeboco/RGBwifi/blob/master/bins/web/use_example.png?raw=true)

### Software and Dependencies
- Arduino IDE 1.8.3
- ESP8266 Board Driver by EP8266 Community. v2.5.0. https://github.com/esp8266/Arduino
- ESP8266 Web Server v1.0.0

### Schematic

![alt text](https://raw.githubusercontent.com/fedeboco/RGBwifi/f5ebdebd468698da88b54962cc8af5251b4130e2/bins/board/rgbcontroller/schematic.png)

