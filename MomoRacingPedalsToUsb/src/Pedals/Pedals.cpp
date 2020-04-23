#include "Arduino.h"
#include "Pedals.h"

Pedals::Pedals(int throttlePin, int brakePin, bool invertThrottle, bool invertBrake, int lowerLimit, int upperLimit){
  _throttle = new Axis(throttlePin, invertThrottle);
  _brake = new Axis(brakePin, invertBrake);
  _lowerLimit = lowerLimit;
  _upperLimit = upperLimit;
}

void Pedals::update(){
  _throttle->update();
  _brake->update();
}

int Pedals::getCombined(){
  _lastUpdate = millis();
  int throttleValue = _throttle->get(_lowerLimit, _upperLimit);
  int brakeValue = _brake->get(_lowerLimit, _upperLimit);
  return (throttleValue - brakeValue + _upperLimit)/2;
}

int Pedals::getThrottle(){
  _lastUpdate = millis();
  return _throttle->get(_lowerLimit, _upperLimit);
}

int Pedals::getBrake(){
  _lastUpdate = millis();
  return _brake->get(_lowerLimit, _upperLimit);
}

int Pedals::getThrottleDigital(){
  return _throttle->get(_lowerLimit, _upperLimit) > 1023 * 0.8 ? 1 : 0;
}

int Pedals::getBrakeDigital(){
  return _brake->get(_lowerLimit, _upperLimit) > 1023 * 0.8 ? 1 : 0;
}

unsigned long Pedals::getLastUpdate(){
  return _lastUpdate;
}