#ifndef MOTORCONTROLLER_INCLUDE
#define MOTORCONTROLLER_INCLUDE

#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include "Motor.h"
#include "PID.h"

#define PI 3.1415926


class MotorController{

  private:
  Motor* _MotorLeft;
  Motor* _MotorRight;
  bool _MotorLeftDir;
  bool _MotorRightDir;

  float _distanceLeft; //distance moved by left wheel in cm
  float _distanceRight; //distance moved by right wheel in cm


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

  //movement and turn at the same time
  //-1 for left turn, 0 for straight, 1 for right turn, but while still moving
  void speedTurn(float speed, float PIDOutput);

//forward movement by given distance (cm) at given speed (0-1)
  void moveDistance(float distance, float speed);

  void encoderUpdate();

};

#endif
