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
#define INVERT_BRAKE true
#define JOYSTICK_LOWER_LIMIT 0
#define JOYSTICK_UPPER_LIMIT 1023
#define DELAY_BETWEEN_UPDATES 5

#include "src/Pedals/Pedals.h"
#include <Joystick.h>

Joystick_ Joystick;

bool reportCombined;
Pedals pedals(THROTTLEPIN, BRAKEPIN, INVERT_THROTTLE, INVERT_BRAKE, JOYSTICK_LOWER_LIMIT, JOYSTICK_UPPER_LIMIT);
int timer;
int needsCalibration;

void setup() {
  Serial.begin(9600);
  reportCombined = true;
  needsCalibration = true; 
  Joystick.begin();
}

void sendAxes(){
  if( reportCombined ){
    Joystick.setRzAxis( pedals.getCombined() );
  }else{
    //Serial.print( pedals.getThrottle() );
    //Serial.print( " " );
    //Serial.println( pedals.getBrake() );
    Joystick.setRxAxis( pedals.getThrottle() );
    Joystick.setRyAxis( pedals.getBrake() );
    //Joystick.setAccelerator( pedals.getThrottle() );
    //Joystick.setBrake( pedals.getBrake() );
    //Serial.print(analogRead(THROTTLEPIN));
    //Serial.print(" ");
    //Serial.println(analogRead(BRAKEPIN));
    //Serial.println("%i %i", analogRead(THROTTLEPIN), analogRead(BRAKEPIN));
  }
}

void loop() {
  timer = millis();
  pedals.update();
  if( timer - pedals.getLastUpdate() > DELAY_BETWEEN_UPDATES ){
    sendAxes();
    /*
    if( needsCalibration && timer > 500 ){
      needsCalibration = false;
      //modeChange()
    }*/
  }
}
