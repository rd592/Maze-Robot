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
  _angle = tempPos;
  _servo.attach(_servoPin);
  _servo.write(tempPos);

  _servoTimer.start();
  while (_servoTimer.read_us() < _waitTime){wait_us(1000);} //detatch servo after a given amount of time to prevent jittering
  _servoTimer.stop();
  _servo.detach();

}

//centre the servo
void ServoController::centre(){
  this->moveTo(90);

}

void ServoController::sweep(int points, int range){
  int arrayCol = 0;
  int start_time = millis();
  moveTo((180-range)/2);
  for(int i = (180 - range)/2; i<= (90+(range/2)); i = i + (range/points)){

    moveTo(i); //move servo, take sensor reading, store in distanceArray
    float distance = _sensor.getOutput(); 
    polarToCartesian(distance, i); //updates _x and _y

    _distanceArrayX[arrayCol] = _x; //stores x coordinate
    _distanceArrayY[arrayCol] = _y; //stores y coordinate

    arrayCol++;
    if(arrayCol >= ARRAYSIZE-1){
      arrayCol = 0;
    }
    wait_us(500);
  }

  centre();

}

//returns pointer to distance arrays
float* ServoController::returnArrayX(){
  return _distanceArrayX;
}

float* ServoController::returnArrayY(){
  return _distanceArrayY;
}

void ServoController::polarToCartesian(float distance, int angle){
  _x = (int)(distance * cos((angle/180)*PI));
  _y = (int)(distance * sin((angle/180)*PI));
}


