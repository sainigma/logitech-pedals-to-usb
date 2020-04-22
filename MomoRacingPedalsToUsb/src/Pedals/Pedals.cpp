#include "Arduino.h"
#include "Pedals.h"

Pedals::Pedals(int throttlePin, int brakePin){
    pinMode(throttlePin, INPUT);
    pinMode(brakePin, INPUT);

    _throttlePin = throttlePin;
    _brakePin = brakePin;
    
    _throttle = 0;
    _brake = 0;
    
    _throttleMax = 0;
    _throttleMin = 1024;
    _brakeMax = 0;
    _brakeMin = 1024;
    _weight = 85;
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