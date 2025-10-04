#if !defined(__SOLAR_MONITOR_H__)
#define __SOLAR_MONITOR_H__
#include "config.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
// #include <stdbool.h>

typedef struct RelayStatus {
  bool relay_1_state;
  bool relay_2_state;
} RelayStatus;

class SolarMonitorServer {
public:
  void present_website(WiFiClient &client, RelayStatus &relay_data);
  void update_json_response(WiFiClient &client, RelayStatus &relay_data);
  void present_modern_website(WiFiClient &client, RelayStatus &relay_data);
  
private:
  void send_html_header(WiFiClient &client);
  void send_modern_css(WiFiClient &client);
  void send_javascript(WiFiClient &client);
};
#endif // !__SOLAR_MONITOR_H__
