#include <mbed.h>
#ifndef IRSENSOR_INCLUDE
#define IRSENSOR_INCLUDE

class IRSensor{
  private:
  char _mux_address;
  char _mux_cmd;
  char _cmd[2];
  float _distance;

  mbed::I2C i2c;
  

  public:

  //inputs are the address of the multiplexer for the IR sensors, and the start register to read from
  IRSensor(char mux_address, char mux_cmd);
  //update sensor reading
  void sensorUpdate();
  
  //return the output in cm
  float getOutput();


} ;


#endif