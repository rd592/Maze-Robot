#include "USSensor.h"



USSensor::USSensor(PinName pin):
  _trigEchoPin(pin), _trigEcho(_trigEchoPin)
{
  
}

float USSensor::avgOutput(){
  float average = 0;

  for(int i = 0; i<=10; i++){
    float temp = getOutput();
    average = average+temp;
    wait_us(1000);

  }
  average = average/10;
  return average;


}

//gives ultrasonic sensor output in cm
float USSensor::getOutput(){
_timer.stop();
_timer.reset();
_trigEcho.output();

_trigEcho = 0;
wait_us(2);

_trigEcho = 1; //10 us pulse to activate trigger pin
wait_us(10);

_trigEcho = 0; //set trigEcho pin back to read mode, wait for pulse
_trigEcho.input(); 

//Serial.println("STOP1");
while(_trigEcho == 0){};
_timer.start();

//Serial.println("STOP2");
while(_trigEcho == 1 && _timer.read_us() < 100000){};

float time = _timer.read_us(); //time the pulse is live for in microseconds
_timer.stop();
_distance = time*0.034/2; //distance calc. 0.034 is speed of sound cm/microseconds. returns microseconds

//Serial.println("STOP3");
//if(_distance >= 200){
//  _distance = 1;
//}
return _distance;
  
}