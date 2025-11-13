#include "ServoController.h"



ServoController::ServoController(int servoPin, PinName sensorPin):
  _servoPin(servoPin), _sensorPin(sensorPin), _sensor(sensorPin)
{ 

}


//move to absolute angular position
void ServoController::moveTo(int angle){
  _servoTimer.reset();
  int tempPos = angle;
  if(angle>180){
    tempPos = 180;
  }
  else if(angle<0){
    tempPos = 0;
  }
  _servo.attach(_servoPin);
  _servo.write(tempPos);

  _servoTimer.start();
  while (_servoTimer.read_us() < _waitTime){wait_us(1000);} //detatch servo after a given amount of time to prevent jittering
  _servoTimer.stop();
  _servo.detach();

}

//centre the servo
void ServoController::centre(){
  _servoTimer.reset();
  _servo.attach(_servoPin);
  _servo.write(90);//90 is the centre of the servos rotation

  _servoTimer.start();
  while(_servoTimer.read_us()<1000000){wait_us(1000);}
  _servoTimer.stop();
  _servo.detach();

}

void ServoController::sweep(int points, int range){
  int arrayCol = 0;
  int start_time = millis();
  for(float i = (180 - range)/2; i<= (90+(range/2)); i = i + (range/points)){
    moveTo(i);
    //_distanceArray[arrayCol][_arrayRow] = _sensor.getOutput(); //this seems to be the problem. might need to implement multithreading
    arrayCol++;
    wait_us(1000);
  }
  
  //Serial.println(_distanceArray[0][0]);
  _arrayRow++;
}


