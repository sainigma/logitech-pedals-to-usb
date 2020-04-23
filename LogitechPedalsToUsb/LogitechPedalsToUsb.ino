/*
  USB Adapter for Momo Racing Wheel pedals.

  The pedals connect with a DB9 male. Wire as so:
    -DB9 pin 4 and/or 9 to VCC
    -DB9 pin 3 and/or 8 to THROTTLEPIN
    -DB9 pin 2 and/or 7 to BRAKEPIN
    -DB9 pin 6 to GND

  Created 22 Apr 2020
  Modified 23 Apr 2020
  by Kari Suominen
*/

/* Configuration */
#define THROTTLEPIN A0
#define BRAKEPIN A1
#define CLUTCHPIN A2
#define CLUTCH_ACTIVE false
#define INVERT_THROTTLE false
#define INVERT_BRAKE true
#define INVERT_CLUTCH false
#define JOYSTICK_LOWER_LIMIT 0
#define JOYSTICK_UPPER_LIMIT 1023
#define DELAY_BETWEEN_UPDATES 5
#define INIT_PHASE_SECONDS 5
/* Configuration end */

#define MODE_ANALOG_COMBINED_DIGITAL 0
#define MODE_ANALOG_SEPARATE_DIGITAL 1
#define MODE_DIGITAL 2

#include "src/Pedals/Pedals.h"
#include <Joystick.h>

Joystick_ Joystick;

int timer;
char activeMode;
bool reportCombined;
bool modeInitialized;
Pedals pedals(THROTTLEPIN, BRAKEPIN, CLUTCHPIN, INVERT_THROTTLE, INVERT_BRAKE, INVERT_CLUTCH, JOYSTICK_LOWER_LIMIT, JOYSTICK_UPPER_LIMIT);


void setup() {
  reportCombined = true;
  modeInitialized = false;
  activeMode = -1;
  Joystick.begin();
}

void initializeMode(){
  bool throttleDown = pedals.getThrottleDigital() > 0;
  bool brakeDown = pedals.getBrakeDigital() > 0;
  if( throttleDown && brakeDown ){
    activeMode = MODE_ANALOG_SEPARATE_DIGITAL;
  }else if( throttleDown ){
    activeMode = MODE_DIGITAL;
  }else if( brakeDown ){
    activeMode = MODE_DIGITAL;
  }else{
    activeMode = MODE_ANALOG_COMBINED_DIGITAL;
  }
  modeInitialized = true;
}

void sendAxes(){
  switch( activeMode ){
    case MODE_ANALOG_COMBINED_DIGITAL:
      Joystick.setRzAxis( pedals.getCombined() );
      if( CLUTCH_ACTIVE ) Joystick.setZAxis( pedals.getClutch() );
      break;
    case MODE_ANALOG_SEPARATE_DIGITAL:
      Joystick.setRxAxis( pedals.getThrottle() );
      Joystick.setRyAxis( pedals.getBrake() );
      Joystick.setButton(0, pedals.getThrottleDigital());
      Joystick.setButton(1, pedals.getBrakeDigital());
      if( CLUTCH_ACTIVE ){
        Joystick.setButton(2, pedals.getClutchDigital());
        Joystick.setZAxis( pedals.getClutch() );
      }
      break;
    case MODE_DIGITAL:
      Joystick.setButton(0, pedals.getThrottleDigital());
      Joystick.setButton(1, pedals.getBrakeDigital());
      if( CLUTCH_ACTIVE ) Joystick.setButton(2, pedals.getClutchDigital());
      break;
  }
}

void loop() {
  timer = millis();
  pedals.update();
  if( timer - pedals.getLastUpdate() > DELAY_BETWEEN_UPDATES ){
    if( !modeInitialized && timer > (INIT_PHASE_SECONDS * 1000) ){
      initializeMode();
    }else{
      sendAxes();
    }
  }
}
