
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

};