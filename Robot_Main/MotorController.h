#ifndef MOTORCONTROLLER_INCLUDE
#define MOTORCONTROLLER_INCLUDE

#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include "Motor.h"


class MotorController{

  private:
  Motor* _MotorLeft;
  Motor* _MotorRight;
  bool _MotorLeftDir;
  bool _MotorRightDir;

  float _distanceLeft;
  float _distanceRight;



  public:

  MotorController(Motor* MotorLeft, Motor* MotorRight);

  void printEncoder();

  float getDistanceLeft();
  float getDistanceRight();


  //controls the turn of the robot, seperate from movement
  //-1 for left turn, 0 for straight, 1 for right turn
  void turn(int direction);

  void turnAngle(float angle, float speed); 

  //controls the speed of the movement
  //1 for forward, 0 for no movement,-1 for backward
  void speed(float speed); 

//forward movement by given distance (cm) at given speed (0-1)
  void moveDistance(float distance, float speed);

  void encoderUpdate();

};

#endif
