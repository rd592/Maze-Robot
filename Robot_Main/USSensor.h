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
  float getOutput(); //single us readings
  float avgOutput();//returns the average of 10 us readings


};

#endif