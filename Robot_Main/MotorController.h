#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include "Motor.h"
#ifndef MOTORCONTROLLER_INCLUDE
#define MOTORCONTROLLER_INCLUDE

class MotorController{

  private:
  Motor* _MotorLeft;
  Motor* _MotorRight;
  bool _MotorLeftDir;
  bool _MotorRightDir;


  public:

  MotorController(Motor* MotorLeft, Motor* MotorRight);

  //controls the turn of the robot, seperate from movement
  //-1 for left turn, 0 for straight, 1 for right turn
  void turn(int direction); 

  //controls the speed of the movement
  //1 for forward, 0 for no movement,-1 for backward
  void move(float speed); 



};

#endif
