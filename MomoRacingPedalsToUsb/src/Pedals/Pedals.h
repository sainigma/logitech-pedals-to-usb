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
    Pedals(int throttlePin, int brakePin, bool invertThrottle, bool invertBrake, int lowerLimit, int upperLimit);
    void update();
    int getCombined();
    int getThrottle();
    int getBrake();
    int getThrottleDigital();
    int getBrakeDigital();
    unsigned long getLastUpdate();
  private:
    Axis *_throttle;
    Axis *_brake;
    int _upperLimit;
    int _lowerLimit;
    unsigned long _lastUpdate;
    char _weight;
};

#endif