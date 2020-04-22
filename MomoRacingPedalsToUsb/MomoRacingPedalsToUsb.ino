/*
  USB Adapter for Momo Racing Wheel pedals.

  The pedals connect with a DB9 male. Wire as so:
    -DB9 pin 4 and/or 9 to VCC
    -DB9 pin 3 and/or 8 to THROTTLEPIN
    -DB9 pin 2 and/or 7 to BRAKEPIN
    -DB9 pin 6 to GND

  Created 22 Apr 2020
  Modified 22 Apr 2020
  by Kari Suominen
*/

#define THROTTLEPIN A0
#define BRAKEPIN A1
#define INVERT_THROTTLE false
#define INVERT_BRAKE false
#define JOYSTICK_LOWER_LIMIT 0
#define JOYSTICK_UPPER_LIMIT 1023
#define DELAY_BETWEEN_UPDATES 16

#include "src/Pedals/Pedals.h"
#include <Joystick.h>

Joystick_ Joystick;

bool reportCombined;
Pedals pedals(THROTTLEPIN, BRAKEPIN, INVERT_THROTTLE, INVERT_BRAKE, JOYSTICK_LOWER_LIMIT, JOYSTICK_UPPER_LIMIT);

void setup() {
  reportCombined = false;
  Joystick.begin();
}

void sendAxes(){
  if( reportCombined ){

  }else{
    Joystick.setAccelerator( pedals.getThrottle() );
    Joystick.setBrake( pedals.getBrake() );
  }
}

void loop() {
  pedals.update();
  if( millis() - pedals.getLastUpdate() > DELAY_BETWEEN_UPDATES ){
    sendAxes();
  }
}
