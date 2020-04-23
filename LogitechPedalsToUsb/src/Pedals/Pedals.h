/*
  Pedals.h - Library for reading values Momo Racing Wheel pedals.
  Created by Kari Suominen, April 22, 2020.
  GNU3
*/

#ifndef Pedals_h
#define Pedals_h

#include "Arduino.h"
#include "Axis.h"

class Pedals{
  public:
    Pedals(int throttlePin, int brakePin, int clutchPin, bool invertThrottle, bool invertBrake, bool invertClutch, int lowerLimit, int upperLimit);
    void update();
    int getCombined();
    int getThrottle();
    int getBrake();
    int getClutch();
    int getThrottleDigital();
    int getBrakeDigital();
    int getClutchDigital();
    unsigned long getLastUpdate();
  private:
    Axis *_throttle;
    Axis *_brake;
    Axis *_clutch;
    int _upperLimit;
    int _lowerLimit;
    unsigned long _lastUpdate;
    char _weight;
};

#endif