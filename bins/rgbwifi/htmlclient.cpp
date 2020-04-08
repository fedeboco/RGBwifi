#include "htmlClient.h"

void htmlClient::listen(WiFiServer & sv) {
  cl = sv.available();
}

bool htmlClient::isConnected() {
  return cl.connected();
}


WiFiClient htmlClient::getClient() {
  return cl;
}

void htmlClient::stop() {
  cl.stop();
}

bool htmlClient::available() {
  return cl.available();
}

htmlClient::htmlClient() {
  currentTime = millis();
  previousTime = 0; 
  timeoutTime = 200;
}

String htmlClient::process(String requestStart) {
    String request = "";
  
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (cl.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (cl.available()) {
        char c = cl.read();
        Serial.write(c);
        request += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            sendWebPage();
            if(request.indexOf(requestStart) >= 0) {
              return request;
            }
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    return "";
}

void htmlClient::sendWebPage() {
  cl.println("HTTP/1.1 200 OK");
  cl.println("Content-type:text/html");
  cl.println("Connection: close");
  cl.println();
         
  cl.println("<!DOCTYPE html>");
  cl.println("<html>");
  cl.println("<script src=\"https://combinatronics.com/fedeboco/RGBwifi/master/bins/web/jscolor.js\"></script>");
  cl.println("<link rel=\"shortcut icon\" href=\"about:blank\">"); // avoids favicon.ico request
    
  cl.println("<head>");
  cl.println("  <style>");
  cl.println("  body {");
  cl.println("    background-color: black;");
  cl.println("  }");
    
  cl.println("  h1 {");
  cl.println("    color: white;");
  cl.println("    font-family: 'Lucida Sans Unicode', 'Arial Narrow Bold', sans-serif;");
  cl.println("    text-align: left;");
  cl.println("  }");
    
  cl.println("  p {");
  cl.println("    color: white;");
  cl.println("    font-family: 'Arial Narrow Bold', sans-serif;");
  cl.println("    font-size: 20px;");
  cl.println("  }");
  cl.println("  </style>");
  cl.println("  </head>");
  cl.println("  <body>");
    
  cl.println("    <h1>RGB WiFi Controller Center</h1>");
  cl.println("    <p>WiFi Board 1</p>");
    
  cl.println("    <font face=\"Lucida Sans Unicode\" color=\"white\"> Pick color: </font>");
  cl.println("    <input class=\"jscolor {onFineChange:'update(this)'}\" id=\"pick\">");
  cl.println("    <button>");
  cl.println("      <a class href=\"#\" color=\"white\" role=\"button\" id=\"choose_color\" face=\"verdana\"> Set Color </a> ");
  cl.println("    </button>");
      
    
  cl.println("  <script>");
  cl.println("    function update(picker) {");
  cl.println("        document.getElementById('pick').innerHTML = \"Elegir \" + Math.round(picker.rgb[0]) + ', ' +  Math.round(picker.rgb[1]) + ', ' + Math.round(picker.rgb[2]);");
  cl.println("        document.getElementById(\"choose_color\").href=\"?x\" + Math.round(picker.rgb[0]) + \"y\" +  Math.round(picker.rgb[1]) + \"z\" + Math.round(picker.rgb[2]) + \"&\";");
  cl.println("    }");
  cl.println("  </script>");
    
  cl.println("  </body>");
  cl.println("  </html>");
  cl.println(); //ends html request
}
