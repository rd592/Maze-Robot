#include "IRSensor.h"


IRSensor::IRSensor(char mux_address, char mux_cmd)
  : _mux_address(mux_address), _mux_cmd(mux_cmd), i2c(P0_31, P0_2)
  {}

void IRSensor::sensorUpdate(){
  i2c.write(_mux_address, &_mux_cmd, 1);
  
  _cmd[0] = 0x5E;
  _cmd[1] = 0x00;

  i2c.write(0x80, _cmd, 1);
  i2c.read(0x80, _cmd, 2);
}

float IRSensor::getOutput(){

  i2c.write(_mux_address, &_mux_cmd, 1);
  
  char nChar[2];
  nChar[0] = 0x35;
  nChar[1] = 0x00; 

  i2c.write(0x80, nChar, 1);
  i2c.read(0x80, nChar, 2);

  int n = (int)nChar[0];//problem with this. Might be becasue shift bit is 3 bits and this is reading 4 bits
  _distance = _cmd[0]*16+_cmd[1]/16/2^n;
  return _distance;

}