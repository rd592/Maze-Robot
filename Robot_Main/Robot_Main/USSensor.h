#ifndef USSENSOR_INCLUDE
#define USSENSOR_INCLUDE

#include <mbed.h>
#include <DigitalInOut.h>

class USSensor{

  private:

  PinName _trigEchoPin;
  mbed::DigitalInOut _trigEcho;
  int _distance;
  int _correction;

  mbed::Timer _sonar;



  public:

  USSensor(PinName pin);
  int getOutput();


};






#endif