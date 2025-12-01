#ifndef SERVOCONTROLLER_INCLUDE
#define SERVOCONTROLLER_INCLUDE

#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include <InterruptIn.h>
#include <Servo.h>
#include "USSensor.h"
#include <Math.h>

#define PI 3.1415926
#define ARRAYSIZE 10 //number of columns in the distance array

class ServoController{

  private:

  const int _waitTime = 600000; //wait time before detaching from pin in microseconds

  int _angle; //servo angular position
  int _servoPin;
  PinName _sensorPin;
  mbed::Timer _servoTimer;

  
  float _distanceArrayX[ARRAYSIZE]; //stores cartesian sensor readings relative to current position. x is [0], y is [1]
  float _distanceArrayY[ARRAYSIZE];

  float _x = 0; //temp x and y 
  float _y = 0;

  Servo _servo;
  USSensor _sensor;

  public:

  //servo pin, and the ultrasonic sensor being used
  ServoController(int servoPin, PinName sensorPin);

  void polarToCartesian(float distance, int angle);
  void moveTo(int angle); //move the servo to a given angle
  void centre(); //centre the servo
  void sweep(int points, int range); //sweep between both ends of the servos range, with a given number of points and angular range
  float* returnArrayX(); // pointer to array of 2 floats
  float* returnArrayY(); // pointer to array of 2 floats
};

#endif