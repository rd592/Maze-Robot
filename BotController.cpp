#include "BotController.h"


BotState currentState = STATE_STOP;


//botcontroller constructor
BotController::BotController(MotorController* motorController, USSensor* USSensor, IRSensor* ir1, IRSensor* ir2, ServoController* servo):
  _motorController(motorController), _us1(USSensor), _ir1(ir1), _ir2(ir2), _servo(servo)
{
}

//updates the robots position based on distance travelled. Only accounts for left motor movement
//sin and cosine might be incorrect way round, needs testing
void BotController::posUpdate(float leftDistance){
  float xDistance = (float)(leftDistance * cos((_theta/180)*PI));
  float yDistance = (float)(leftDistance * sin((_theta/180)*PI));
  
  _x = _x + xDistance; //update absolute positions
  _y = _y + yDistance;
}


//used to change the objects speed variable, does not update motor speed
void BotController::setSpeed(float speed){
  _speed = speed;
}

//update all sensor readings
void BotController::sensorUpdate(){
  _us1Out = _us1->avgOutput();
  _ir1Out = _ir1->avgOutput();
  _ir2Out = _ir2->avgOutput();
}

//turns bot by specified angle, positive, or negative
void BotController::turnAngle(float angle){
  _motorController->turnAngle(angle, _speed);
  _theta = _theta + angle; //theta is only ever updated by +-90 degrees for now
}

//sets wheel turn value and speed
void BotController::turn(int direction, float speed){

  _motorController->speed(speed);
  _motorController->turn(direction);
}

//updates motor speed
void BotController::speed(float speed){
  _motorController->speed(speed);
}

//move by a set distance without checks. moveUntil is superior
void BotController::moveDistance(float distance){
  _motorController->moveDistance(distance, _speed);
}


//moves until something is detected in front, PID implemented to stay a set distance from a wall
void BotController::moveUntil(float distance, float stoppingDistance){

  //average of both wheels distance
  float currentDistance = (_motorController->getDistanceLeft()+_motorController->getDistanceRight())/2;

  //loop until obstacle detected or distance reached
  while(abs((_motorController->getDistanceLeft()+_motorController->getDistanceRight())/2) <abs(distance)){
    double error = (double)((_ir1Out+_ir2Out)/2);
    sensorUpdate();

    double PIDAdjust = pid.computePID(error, 10); //computes PID input value based on difference between sensors
    Serial.println(PIDAdjust);

    //stop if an obstacle in front
    if(_us1Out <= stoppingDistance){
      _motorController->speed(0.0f);
      posUpdate(((_motorController->getDistanceLeft()+_motorController->getDistanceRight())/2)-currentDistance);
      _blockedFront = 1;
      _stopped = 1;
      break;
    }
    //*****************
    //***************** REMOVE WALLALIGN FROM FUNCTION CALL AND FSM

    _motorController->speedTurn(_speed, PIDAdjust); //speed function adjusted for PID output

  }
  _motorController->speed(0.0f); //turn off motors once destination reached, update position
  posUpdate(_motorController->getDistanceLeft()-currentDistance);

  _mapping = 1; //after moving set distance successfully, perform mapping
}

//function to align to right side wall. Could maybe implement slight forward movement to make sensor averaging more accurate?
void BotController::wallAlign(){

  float ir1Out = _ir1->avgOutput();
  float ir2Out = _ir2->avgOutput();
  
  if(ir1Out>ir2Out){

    while(ir1Out>ir2Out){
      turn(1, 0.5f);
      ir1Out = _ir1->avgOutput();
      ir2Out = _ir2->avgOutput(); 
      wait_us(100);
    }

  }
  else{
    while(ir1Out<ir2Out){
      turn(-1, 0.5f);
      ir1Out = _ir1->avgOutput();
      ir2Out = _ir2->avgOutput(); 
      wait_us(100);
    }
    
    
  }
  turn(0, _speed);//reset turn and speed
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
    //wallAlign();

    //if not stopped in front
    if(_stopped == 0){
      //if a wall is on the right, can continue
      if(_ir1Out < _wallDetectionDistance || _ir2Out < _wallDetectionDistance){
        
        moveUntil(20,_stoppingDistance);
      }
      
      //if no wall on right, turn right
      else{
        _noWall = 1; 
        moveUntil(5,_stoppingDistance); //prevents wall collision
        turnAngle(90);
        moveUntil(10,_stoppingDistance); //keep moving until back to a wall
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
  
  _distanceArrayX = _servo->returnArrayX();//returns the array of obstacles in front, and their positions in cartesian space relative to the sensor. Needs to be added to bot position
  _distanceArrayY = _servo->returnArrayY();
}

void BotController::map(){
  sweep(8, 140); //perform an ultrasonic sensor sweep, 8 points, 140 degrees rotation

  //implement actual mapping procedure 

  _mapping = 0; //return to not mapping
}




// *******Finite State Machine Implementation ********




void BotController::fsmStart(){


  switch(currentState){
    //from stop, can go to mapping, moving, turn left, turn right, or stay in stop
    case STATE_STOP:
      speed(0.0f);
      //if mapping is true, go to mapping state
      if(_mapping){
        currentState = STATE_MAP;
      }
      //if aligning, go to aligning state
      else if(_aligning){
        currentState = STATE_ALIGN;
      }
      //logic for if the robot is blocked
      else if(_blockedFront && _blockedRight){
        //if blocked from right and front, turn left
        currentState = STATE_LEFT;
      }
      //if no wall on right, turn right
      else if(!_blockedRight){
        currentState = STATE_RIGHT;
      }
      else if(!_blockedFront){
        currentState = STATE_FORWARD;

      }
      
      break;

    //from forward, can go to stop
    case STATE_FORWARD:

      //stop if changing state, or blocked, or if no wall on right
      if(_aligning || _mapping || _blockedFront || !_blockedRight){
        currentState = STATE_STOP;
      }
      //if not changing state, move forward by 5 cm
      else{
        moveUntil(5, _stoppingDistance);
      }

      break;

    //after moving backwards once, go back to stop state. currently not implemented
    case STATE_BACKWARD:
      speed(-_speed);
      currentState = STATE_STOP;
      break;
    
    //after turning, go back to stop
    case STATE_LEFT:
      turnAngle(-90);
      currentState = STATE_STOP;
      break;

    case STATE_RIGHT:
      turnAngle(90);
      currentState = STATE_STOP;
      break;
    
    //align with right side wall
    case STATE_ALIGN:
      wallAlign();

      currentState = STATE_STOP;
      break;

    //map area in front
    case STATE_MAP:
      map();

      currentState = STATE_STOP;
      break;
  }
}



