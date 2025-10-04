#if !defined(RELAY_CONTROL_H)
#define RELAY_CONTROL_H
#include <Arduino.h>
#include <stdint.h>

struct Relay {
  uint8_t pin;
  bool state;
};

class RelayControl {
public:
  RelayControl(Relay *r1, Relay *r2);
  ~RelayControl();

  void init();
  void setRelay(Relay *relay, bool state);
  bool getRelay(Relay *relay);

private:
  Relay relays[2];
};

#endif
