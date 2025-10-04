#include "config.h"
#include <Arduino.h>

#include <ESP8266WiFi.h>

#include "relay_control.h"
#include "solar_monitor_server.h"
#include "wifi_configs.h"

WiFiServer server(80);

String header;
// For wifi Server

unsigned long currentTime = millis();
unsigned long previousTime = 0;

SolarMonitorServer Solar_monitor_server;

WiFiConfigs Wifi_configs;
Relay r1{RELAY_1_PIN, false};
Relay r2{RELAY_2_PIN, false};

// Create a Relay Control Object
RelayControl Relay_Control(&r1, &r2);

RelayStatus relay_status;
RelayStatus new_data;

void update_reading() {
  relay_status.relay_1_state = Relay_Control.getRelay(&r1);
  relay_status.relay_2_state = Relay_Control.getRelay(&r2);
  new_data.relay_1_state = relay_status.relay_1_state;
  new_data.relay_2_state = relay_status.relay_2_state;
}

void setup() {
  Serial.begin(BAUD_RATE);
  Wifi_configs.connect();
  server.begin();
  Relay_Control.init();
}

void loop() {
  update_reading();

  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= TIMEOUT_MS) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            if (header.indexOf("GET /data") >= 0 ||
                header.indexOf("GET /data/?=") >= 0) {
#if defined(DEBUG_EVERYTHING)
              Serial.println("Serving Json Response");
#endif
              Solar_monitor_server.update_json_response(client, relay_status);

              if (header.indexOf("GET /data?relay1=on") >= 0) {
                Serial.println("Relay 1 ON");
                Relay_Control.setRelay(&r1, true);
              } else if (header.indexOf("GET /data?relay1=off") >= 0) {
                Serial.println("Relay 1 OFF");
                Relay_Control.setRelay(&r1, false);
              } else if (header.indexOf("GET /data?relay2=on") >= 0) {
                Serial.println("Relay 2 ON");
                Relay_Control.setRelay(&r2, true);
              } else if (header.indexOf("GET /data?relay2=off") >= 0) {
                Serial.println("Relay 2 OFF");
                Relay_Control.setRelay(&r2, false);
              }
              break;
            } else {
#if defined(DEBUG_EVERYTHING)
              Serial.println("Serving HTML");
#endif
              Solar_monitor_server.present_website(client, new_data);
              break;
            }
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
#if defined(DEBUG_EVERYTHING)
    Serial.println("Client disconnected.");
#endif
  }
  delay(100);
}
