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
    Pedals(int throttlePin, int brakePin);
    void update();
    int getThrottle();
    int getBrake();
  private:
    void calibrate();
    char _throttlePin;
    int _throttle;
    int _throttleMin;
    int _throttleMax;

    char _brakePin;
    int _brake;
    int _brakeMin;
    int _brakeMax;

    char _weight;
};

#endif