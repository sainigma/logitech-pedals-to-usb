#define THROTTLEPIN A0
#define BRAKEPIN A1
#include "src/Pedals/Pedals.h"

Pedals pedals(THROTTLEPIN, BRAKEPIN);

void setup() {
}

void loop() {
  pedals.update();
  delay(100);
}
