#ifndef SERVOCONTROLLER_INCLUDE
#define SERVOCONTROLLER_INCLUDE

#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include <InterruptIn.h>
#include <Servo.h>
#include "USSensor.h"

class ServoController{

  private:

  const int _waitTime = 600000; //wait time before detaching from pin in microseconds

  int _angle; //servo angular position
  int _servoPin;
  PinName _sensorPin;
  mbed::Timer _servoTimer;

  
  int _distanceArray[8][10];
  int _arrayRow;

  Servo _servo;
  USSensor _sensor;

  public:

  //servo pin, and the ultrasonic sensor being used
  ServoController(int servoPin, PinName sensorPin);

  void moveTo(int angle); //move the servo to a given angle
  void centre(); //centre the servo
  void sweep(int points, int range); //sweep between both ends of the servos range, with a given number of points and angular range

};

#endif