#include "IRSensor.h"


IRSensor::IRSensor(char mux_address, char mux_cmd)
  : _mux_address(mux_address), _mux_cmd(mux_cmd), i2c(P0_31, P0_2)
  {}


int IRSensor::getOutput(){

  //write the default addresses to access the correct sensor
  i2c.write(_mux_address, &_mux_cmd, 1);
  
  //finds the start point for IR measurement. distance is from address 0x5E to 0x60
  _cmd[0] = 0x5E;
  _cmd[1] = 0x00; 

  //write the address to read, then read the data in that address
  i2c.write(0x80, _cmd, 1);
  i2c.read(0x80, _cmd, 2);

  //distance calculation returning in mm
  _distance = _cmd[0]*16+_cmd[1]/16/2^2;
  return _distance;

}