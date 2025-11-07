#ifndef SERVOCONTROLLER_INCLUDE
#define SERVOCONTROLLER_INCLUDE

#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include <InterruptIn.h>

#include <Servo.h>
#include "Timer.h"

class ServoController{

  private:
  Servo _servo;
  int _position;
  int _servoPin;
  ArduinoTimer _servoTimer;
  

  public:

  ServoController(Servo* servo, PinName pin);

  void moveTo(int position);
  void centre();

  //might need to all be rewritten to instead be a library of functions to move servos without including the servo object.
  //so the function itself also contains a call to whatever servo is being updated
  //there is already a built in mbed timer so use that

};

#endif