#include "Arduino.h"
#include "Pedals.h"
#define THROTTLE true
#define BRAKE false

Pedals::Pedals(int throttlePin, int brakePin, bool invertThrottle, bool invertBrake, int lowerLimit, int upperLimit){
    pinMode(throttlePin, INPUT);
    pinMode(brakePin, INPUT);

    _throttlePin = throttlePin;
    _brakePin = brakePin;
    
    _throttle = 0;
    _brake = 0;
    
    _throttleInvert = invertThrottle;
    _brakeInvert = invertBrake;

    _throttleMax = 0;
    _throttleMin = 1024;
    _brakeMax = 0;
    _brakeMin = 1024;
    
    _weight = 85;
    _lastUpdate = 0;
    _lowerLimit = lowerLimit;
    _upperLimit = upperLimit;
}

void Pedals::update(){
  int throttleRaw = analogRead(_throttlePin);
  int brakeRaw = analogRead(_brakePin);

  _throttle = _weight * throttleRaw + (1 - _weight) * _throttle;
  _brake = _weight * brakeRaw + (1 - _weight) * _brake;
  calibrate();
}

void Pedals::calibrate(){
  if( _throttle > _throttleMax ){
    _throttleMax = _throttle;
  }
  if( _throttle < _throttleMin ){
    _throttleMin = _throttle;
  }
  if( _brake > _brakeMax ){
    _brakeMax = _brake;
  }
  if( _brake < _brakeMin ){
    _brakeMin = _brake;
  }
}

int Pedals::getPedal(bool pedalType){
  _lastUpdate = millis();
  bool invert;
  int value;
  int minValue;
  int maxValue;
  if( pedalType == THROTTLE ){
    invert = _throttleInvert;
    value = _throttle;
    minValue = _throttleMin;
    maxValue = _throttleMax;
  }else{
    invert = _brakeInvert;
    value = _brake;
    minValue = _brakeMin;
    maxValue = _brakeMax;
  }
  if( invert ){
    value = 1023 - value;
  }
  return map(value, minValue, maxValue, _lowerLimit, _upperLimit);
}


int Pedals::getThrottle(){
  return getPedal(THROTTLE);
}

int Pedals::getBrake(){
  return getPedal(BRAKE);
}

unsigned long Pedals::getLastUpdate(){
  return _lastUpdate;
}