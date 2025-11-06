#include "ServoController.h"

/*
ServoController::ServoController(Servo* servo, PinName pin):
_servo(servo), _servoPin(pin)

{}

//move to absolute angular position
void ServoController::moveTo(int position){
  tempPos = position;
  if(position>180){
    tempPos = 180;
  }
  else if(position<0){
    tempPos = 0;
  }

  _servo.attach(_servoPin);
  _servo.write(tempPos);

  //timer to allow servo to reach destination, then detach to stop jittering
  bool timerDone = 0;
  _servoTimer.start();
  while(!timerDone){
    if(_servoTimer.getTimer()>=100){
      _servoTimer.stop();
      _servo.detach();
      timerDone = 1;
    }
  }

}

//centre the servo
void ServoController::centre(){
  _servo.attach(_servoPin);
  _servo.write(92);//92 is the centre of the servos rotation

    //timer to allow servo to reach destination, then detach to stop jittering
  bool timerDone = 0;
  _servoTimer.start();
  while(!timerDone){
    if(_servoTimer.read()>=100){
      _servoTimer.stop()
      _servo.detach();
      timerDone = 1;
    }
  }
}
*/