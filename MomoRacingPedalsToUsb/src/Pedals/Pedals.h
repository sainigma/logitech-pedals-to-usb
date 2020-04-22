/*
  Pedals.h - Library for reading values Momo Racing Wheel pedals.
  Created by Kari Suominen, April 22, 2020.
  GNU3
*/

#ifndef Pedals_h
#define Pedals_h

#include "Arduino.h"

class Pedals{
  public:
    Pedals(int throttlePin, int brakePin, bool invertThrottle, bool invertBrake, int lowerLimit, int upperLimit);
    void update();
    int getThrottle();
    int getBrake();
    unsigned long getLastUpdate();
  private:
    int getPedal(bool pedalType);
    void calibrate();
    char _throttlePin;
    int _throttle;
    int _throttleMin;
    int _throttleMax;
    bool _throttleInvert;

    char _brakePin;
    int _brake;
    int _brakeMin;
    int _brakeMax;
    bool _brakeInvert;

    int _lowerLimit;
    int _upperLimit;
    unsigned long _lastUpdate;
    char _weight;
};

#endif