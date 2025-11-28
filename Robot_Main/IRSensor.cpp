#include "IRSensor.h"


IRSensor::IRSensor(char mux_address, char mux_cmd)
  : _mux_address(mux_address), _mux_cmd(mux_cmd), i2c(P0_31, P0_2)
  {}


float IRSensor::avgOutput(){
  float average = 0;

  for(int i = 0; i<10; i++){
    float temp = getOutput();
    average = average+temp;
    wait_us(100);

  }
  average = average/10;
  return average;

}

float IRSensor::getOutput(){

  //write the default addresses to access the correct sensor
  i2c.write(_mux_address, &_mux_cmd, 1);
  wait_us(50);
  //finds the start point for IR measurement. distance is from address 0x5E to 0x60
  _cmd[0] = 0x5E;
  _cmd[1] = 0x00; 
  char reg = 0x5E;


  //write the address to read, then read the data in that address
  i2c.write(0x80, &reg, 1);
  wait_us(50);
  i2c.read(0x80, _cmd, 2);

  //distance calculation returning in cm
  uint16_t raw = ((uint16_t)_cmd[0]<<4)|(_cmd[1]>>4);

  //Read scale factor
  char k_reg = 0x35;
  i2c.write(0x80, &k_reg, 1);
  char K;
  i2c.read(0x81, &K, 1);

  // Convert to cm
  _distance = ((raw*K)/160.0f)*1.22; //1.22 is correction

  //if(_distance > 200){
    //_distance = 1;
  //}
  return _distance;

}