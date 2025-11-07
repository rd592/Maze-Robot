#include "USSensor.h"



USSensor::USSensor(PinName pin):
  _trigEchoPin(pin), _trigEcho(_trigEchoPin)
{
  
}

int USSensor::getOutput(){

  _sonar.reset();
  _sonar.start();

  while(_trigEcho==2){

  }
  _sonar.stop();
  _correction = _sonar.read_us();

  _trigEcho = 1;
  _sonar.reset();
  wait_us(10);
  _trigEcho = 0;

  while(_trigEcho==0){}
  _sonar.start();

  while(_trigEcho==1){}
  _sonar.stop();

  _distance = (_sonar.read_us()-_correction)/58.0;
  return _distance;

  
}