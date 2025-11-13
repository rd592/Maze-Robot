#include "MotorController.h"


MotorController::MotorController(Motor* MotorLeft, Motor* MotorRight):
  _MotorLeft(MotorLeft), _MotorRight(MotorRight){}

//change the direction of turn of the motors.
void MotorController::turn(int direction){

  //0 is backwards, 1 is forwards

  //turn right
  if(direction >0){
    _MotorLeftDir = 1;
    _MotorRightDir = 0;
  }
  //turn left
  else if(direction < 0){
    _MotorLeftDir = 0;
    _MotorRightDir = 1;
  }
  //no turn
  else{
    _MotorLeftDir = 1;
    _MotorRightDir = 1;
  }

}

void MotorController::printEncoder(){
  Serial.println(_MotorLeft->getEncoder());
  Serial.println(_MotorRight->getEncoder());
}

//controlls the speed of movement, call this to move.
void MotorController::move(float speed){

  int moveDir = 0;
  if (speed >= 0){
    moveDir = 1;
  }
  else{
    moveDir = 0;
  }
  
  _MotorLeft->setDirection(_MotorLeftDir*moveDir);
  _MotorRight->setDirection(_MotorRightDir*moveDir);

  _MotorLeft->setDutyCycle(abs(speed));
  _MotorRight->setDutyCycle(abs(speed));
}
//Still need to implement actual revolutions 
void MotorController::encoderUpdate(){
  _MotorLeft->encUpdate();
  _MotorRight->encUpdate();
}