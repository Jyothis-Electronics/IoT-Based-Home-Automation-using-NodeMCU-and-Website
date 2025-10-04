#include "relay_control.h"
// #include <stdint.h>

RelayControl::RelayControl(Relay *r1, Relay *r2) {
  relays[0] = *r1;
  relays[1] = *r2;
}
RelayControl::~RelayControl() {}

void RelayControl::init() {
  for (int i = 0; i < 2; i++) {
    pinMode(relays[i].pin, OUTPUT);
    digitalWrite(relays[i].pin, LOW);
    relays[i].state = false;
  }
}
void RelayControl::setRelay(Relay *relay, bool state) {
  if (state) {
    digitalWrite(relay->pin, HIGH);
    relay->state = true;
  } else {
    digitalWrite(relay->pin, LOW);
    relay->state = false;
  }
}

bool RelayControl::getRelay(Relay *relay) { return relay->state; }
