#ifndef Axis_h
#define Axis_h
#include "Arduino.h"
class Axis{
  public:
    Axis(int pin, bool invert);
    void update();
    int get(int lowerLimit, int upperLimit);
  private:
    bool _invert;
    char _pin;
    int _value;
    int _sum;
    char _n;
    char _samples;
    int _min;
    int _max;
};
#endif