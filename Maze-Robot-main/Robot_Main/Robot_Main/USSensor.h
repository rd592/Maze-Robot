#ifndef USSENSOR_INCLUDE
#define USSENSOR_INCLUDE

#include <mbed.h>
#include <DigitalInOut.h>

class USSensor{

  private:

  PinName _trigEchoPin;
  mbed::DigitalInOut _trigEcho;
  float _distance;

  mbed::Timer _timer;

  public:

  USSensor(PinName pin);
  float getOutput();


};

#endif