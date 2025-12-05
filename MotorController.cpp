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

//this function works by calculating the angular distance needed to turn based on the known turning perimeter (44cm)

//time for 1 rotation is 3.2s
//distance between wheels = 14cm
//perimeter = 44cm
void MotorController::turnAngle(float angle, float moveSpeed){

  //convert angle to distance
  float perimeter = 44;
  float angleRatio = abs(angle)/360;
  float angularDistance = perimeter*angleRatio; //distance the motors need to move

  //turn right
  if(angle >0){
    _MotorLeftDir = 1;
    _MotorRightDir = 0;
  }
  //turn left
  else{
    _MotorLeftDir = 0;
    _MotorRightDir = 1;
  }

  moveDistance(angularDistance, moveSpeed);

  //reset motor direction
  _MotorLeftDir = 1;
  _MotorRightDir = 1;

}

//adjust for encoder measurements per rotation, gear ratio, then distance moved per rotation (4.8 = wheel size cm, 3.1415 = pi)
float MotorController::getDistanceLeft(){
  _distanceLeft = (((float)_MotorLeft->getEncoder()/6)/298)*PI*4.8;
  return _distanceLeft; 
}
float MotorController::getDistanceRight(){
  _distanceRight = (((float)_MotorRight->getEncoder()/6)/298)*PI*4.8;
  return _distanceRight;
}

void MotorController::printEncoder(){
  float motorLeftCm = getDistanceLeft();
  float motorRightCm = getDistanceRight();

}


void MotorController::moveDistance(float distance, float moveSpeed){
  float startMotorLeft = getDistanceLeft();
  float startMotorRight = getDistanceRight();

  //if direction is negative, move backwards. direction can be controlled with distance or speed
  int direction = 1;
  if(distance < 0){
    direction = -1;
  }


  float startTime = millis();

//loop movement until encoder reads the right value
  while(abs(getDistanceLeft()-startMotorLeft) <abs(distance)){
    speed(moveSpeed*direction);
    wait_us(100);
  }
  speed(0);
}

//controlls the speed of movement, call this to move.
void MotorController::speed(float speed){
  
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

//similar function to speed, just addition of independently set motor left and right speeds based on PID error
void MotorController::speedTurn(float speed, float PIDOutput){
  
  int moveDir = 0;
  if (speed >= 0){
    moveDir = 1;
  }
  else{
    moveDir = 0;
  }

  //L and R are the speed multipliers for the left and right motor based on the PID input
  //if PID returns anything other than 0, motors need adjusting.
  float L = PIDOutput+1.0f;
  if(L > 1.0f){
    L = 1.0f;
  }
  float R = 1.0f-PIDOutput;
  if(R > 1.0f){
    R = 1.0f;
  }
  
  _MotorLeft->setDirection(_MotorLeftDir*moveDir);
  _MotorRight->setDirection(_MotorRightDir*moveDir);

  _MotorLeft->setDutyCycle(fabs(speed*R));
  _MotorRight->setDutyCycle(fabs(speed*L));
}

