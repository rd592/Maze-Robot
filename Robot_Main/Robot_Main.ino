using namespace mbed;
#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include <InterruptIn.h>

#include "Motor.h"
#include "MotorController.h"
#include "IRSensor.h"
#include <Servo.h>
//#include "ServoController.h"

  //pins for the motors
  PinName APow = P0_27;
  PinName BPow = P1_2;
  PinName ADir = P0_4;
  PinName BDir = P0_5; 

  //servo signal pin
  int servoSig = 4;

  //left and right motor, and the motor controller objects
  Motor* motorA;
  Motor* motorB;
  MotorController* controller;

  IRSensor* ir1;

  Servo* servo;
  //ServoController* servoController;
  int servoPos = 0;

  //mbed::I2C* i2c;
  char cmd[2];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //set up motor objects and controller
  motorA = new Motor(ADir, APow, 1);
  motorB = new Motor(BDir, BPow, 0);
  controller = new MotorController(motorA, motorB);
  //set motors to idle
  controller->turn(0);
  controller->move(0);

  //set up IR sensor
  ir1 = new IRSensor(0x01, 0xEE);

  //set up servo
  //servo->attach(servoSig);
  //servo->write(88);

  
  //i2c = new I2C(P0_31, P0_2);
}

float temp = 0; //for I2C
int temp2 = 0;
void loop() {

  ir1->sensorUpdate();
  temp = ir1->getOutput();
  //Serial.println(temp);

  //reset motor movement
  controller->move(0);

  //wasd movement
  if(Serial.available() >0){
    char input = Serial.read();
    if(input == 'w'){
      controller->turn(0);
      controller->move(1);
      
      wait_us(1000000);
    }
    if(input == 'a'){
    controller->turn(-1);
    controller->move(0.8f);
  
    wait_us(1000000);
    }

    if(input == 'd'){
    controller->turn(1);
    controller->move(0.8f);
  
    wait_us(1000000);
    }
    if(input == 's'){
    controller->turn(0);
    controller->move(-0.8f);
  
    wait_us(1000000);
    }


  }

/*
  Serial.println(servo.read());
  if(servo->read() == 86){
    temp2 += 1;
    if(temp2 >= 1000){
          servo->detach();
          temp2 = 0;
    }

  }
  */
  
  
}


