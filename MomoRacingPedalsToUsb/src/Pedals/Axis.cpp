#include "Arduino.h"
#include "Axis.h"

Axis::Axis(int pin, bool invert){
  pinMode(pin, INPUT);
  _pin = pin;
  _invert = invert;
  _value = 0;
  _sum = 0;
  _n = 0;
  _samples = 16;
  _min = 1023;
  _max = 0;
}

void Axis::update(){
  int rawValue = analogRead(_pin);
  if( _n < _samples ){
    _n++;
    _sum += rawValue;
  }else{
    _value = (int)( _sum/(double)_n );
    _min = min(_min, _value);
    _max = max(_max, _value);
    _n = 0;
    _sum = 0;
  }
}

int Axis::get(int lowerLimit, int upperLimit){
  int result,calibMin,calibMax;
  if( _invert ){
    result = 1023 - _value;
    calibMin = 1023 - _max;
    calibMax = 1023 - _min;
  }else{
    result = _value;
    calibMin = _min;
    calibMax = _max;
  }
  if( result > 1023 ) result = 1023;
  else if( result < 0 ) result = 0;
  return map(result, calibMin, calibMax, lowerLimit, upperLimit);
}