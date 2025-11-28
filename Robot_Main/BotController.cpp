#include "BotController.h"

BotController::BotController(MotorController* motorController, USSensor* USSensor, IRSensor* ir1, IRSensor* ir2, ServoController* servo):
  _motorController(motorController), _us1(USSensor), _ir1(ir1), _ir2(ir2), _servo(servo)
{
}


void BotController::setSpeed(float speed){
  _speed = speed;
}

//update all sensor readings
void BotController::sensorUpdate(){
  _us1Out = _us1->avgOutput();
  wait_us(100); //processor breathing time
  _ir1Out = _ir1->avgOutput();
  _ir2Out = _ir2->avgOutput();
}

void BotController::turnAngle(float angle){
  _motorController->turnAngle(angle, _speed);
}

void BotController::speed(float speed){
  _motorController->speed(speed);
}

void BotController::moveDistance(float distance){
  _motorController->moveDistance(distance, _speed);
}


//moves until something is detected in front
void BotController::moveUntil(float distance, float stoppingDistance){

  float currentDistance = _motorController->getDistanceLeft(); //only uses left side motor distance, shouldnt be a problem

  //loop until distance is too close
  while(abs(_motorController->getDistanceLeft()-currentDistance) <abs(distance)){
    sensorUpdate();

    //stop if an obstacle in front
    if(_us1Out <= stoppingDistance){
      _motorController->speed(0);
      _stopped = 1;
      break;
    }
    _motorController->speed(_speed);

    wait_us(1000);
  }
}

//function to align to right side wall
void BotController::wallAlign(){

  float ir1Out = _ir1->avgOutput();
  float ir2Out = _ir2->avgOutput();
  
  if(ir1Out>ir2Out){

    while(ir1Out>ir2Out){
      turnAngle(1);
      ir1Out = _ir1->avgOutput();
      ir2Out = _ir2->avgOutput(); 
      wait_us(100);
    }

  }
  else{
    while(ir1Out<ir2Out){
      turnAngle(-1);
      ir1Out = _ir1->avgOutput();
      ir2Out = _ir2->avgOutput(); 
      wait_us(100);
    }
    
  }

}
//follow a wall, stopping every 10 cm to check environment

/*
Logic:
if not stopped by a wall in front, and a wall is detected on the right, keep going forward.
if not stopped by a wall in front, and no wall is detected on the right, turn right, go forward.
  Once stopped by a wall in front again, turn left and continue.
if stopped by a wall in front and a wall is detected on the right, turn 90 degrees left, then continue

*/
void BotController::wallFollow(){
  _stopped = 0;
  _noWall = 0;
  while(1){
    sensorUpdate();
    wallAlign();

    //if not stopped in front
    if(_stopped == 0){
      //if a wall is on the right, can continue
      if(_ir1Out < _wallDetectionDistance || _ir2Out < _wallDetectionDistance){
        
        moveUntil(5,_stoppingDistance);
      }
      
      //if no wall on right, turn right
      else{
        _noWall = 1; 
        moveUntil(5,_stoppingDistance); //prevents wall collision
        turnAngle(90);
        moveUntil(5,_stoppingDistance); //keep moving until back to a wall
      }
      
      
    }
    
    //if stopped, only ever need to turn left
    else if(_stopped == 1){
      //turn back to normal direction if trying to find wall
      if(_noWall){
        _noWall = 0;

      }
      _stopped = 0;
      turnAngle(-90);
      moveUntil(5,_stoppingDistance); //keep moving until back to a wall
    }
    
    

    wait_us(10000);
  }
}


void BotController::sweep(int points, int angleRange){
  _servo->sweep(points, angleRange);
  
  _distanceArray = _servo->returnArray();
}





