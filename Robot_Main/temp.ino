
/*
#include "ServoController.h"


ServoController::ServoController(PinName pin):
_servoPin(pin), _servo(pin)
{

}

//move to absolute angular position
void ServoController::moveTo(int position){
  int tempPos = position;
  if(position>180){
    tempPos = 180;
  }
  else if(position<0){
    tempPos = 0;
  }

  _servo.attach(_servoPin);
  _servo.write(tempPos);

  //timer to allow servo to reach destination, then detach to stop jittering
  _servoTimer.reset();
  _servoTimer.start();
  while(_servoTimer.read_us()<=100){};

  _servoTimer.stop();
  _servo.detach();

}

//centre the servo
void ServoController::centre(){
  _servo.attach(_servoPin);
  _servo.write(92);//92 is the centre of the servos rotation

    //timer to allow servo to reach destination, then detach to stop jittering
  _servoTimer.reset();
  _servoTimer.start();

  while(_servoTimer.read_us()<=100){};

  _servoTimer.stop();
  _servo.detach();
}
*/