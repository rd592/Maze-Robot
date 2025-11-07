#ifndef IRSENSOR_INCLUDE
#define IRSENSOR_INCLUDE

#include <mbed.h>

class IRSensor{
  private:
  char _mux_address;
  char _mux_cmd;
  char _cmd[2];
  int _distance;

  mbed::I2C i2c;
  

  public:

  //inputs are the address of the multiplexer for the IR sensors, and the IR sensor bus address
  IRSensor(char mux_address, char mux_cmd);
  
  //return the output in mm
  int getOutput();


} ;


#endif