using namespace mbed;
#include <mbed.h>
#include <DigitalOut.h>
#include <DigitalIn.h>
#include <PwmOut.h>
#include <InterruptIn.h>

#include "Motor.h"
#include "MotorController.h"
#include "IRSensor.h"
#include "USSensor.h"
#include "ServoController.h"

#include "BotController.h"

  //pins for the motors
  PinName APow = P0_27;
  PinName BPow = P1_2;
  PinName ADir = P0_4;
  PinName BDir = P0_5; 
  PinName AEnc = P1_11;
  PinName BEnc = P1_12;

  //pin for the ultrasound sensor
  PinName TrigEcho = P0_23;

  //servo signal pin
  int servoSig = 4;
  PinName servoPin = P1_15;

  //pin for button input
  PinName buttonIn = P0_28;



  //left and right motor, and the motor controller objects
  Motor* motorA;
  Motor* motorB;
  MotorController* controller;

  IRSensor* ir1;
  float ir1Out; //infrared 1 reading
  IRSensor* ir2;
  float ir2Out;

  USSensor* us1;
  float us1Out; //ultrasound reading

  ServoController* servo;
  Servo myServo;


  BotController* botController; //overall bot controller


  //rtos::Thread mapThread; //will be used for us sensor movement and mapping to prevent processor starvation


  //mbed::I2C* i2c;
  char cmd[2];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  //set up motor objects and controller
  motorA = new Motor(ADir, APow, 1, AEnc, 0.974);
  motorB = new Motor(BDir, BPow, 0, BEnc, 1);
  controller = new MotorController(motorA, motorB);

  //set motors to idle
  controller->turn(0);
  controller->speed(0);
  controller->encoderUpdate();

  //set up IR sensors
  ir1 = new IRSensor(0xEE, 0b0001); //IR bus 0
  ir2 = new IRSensor(0xEE, 0b0010); //IR bus 1


  //set up US Sensor
  us1 = new USSensor(TrigEcho);

  servo = new ServoController(servoSig, TrigEcho);
  
  //servo sweep needs multithreading as it uses a lot of wait functions
  myServo.attach(servoSig);
  //servo->sweep(4, 140);
  
  botController = new BotController(controller, us1, ir1, ir2, servo);
  botController->setSpeed(0.8f);
 
}


int temp2 = 0;
void loop() {
  
  us1Out = us1->avgOutput();

  //Serial.println("us1 output:");
  //Serial.println(us1Out);

  ir1Out = ir1->getOutput();

  //Serial.println("ir1 output:");
  //Serial.println(ir1Out);
    ir2Out = ir2->getOutput();

  //Serial.println("ir2 output:");
  //.println(ir2Out);


  //botController->wallFollow();
    

  //wasd movement
  if(Serial.available() >0){

    char input = Serial.read();

    if(input == 'w'){
      //botController->turnAngle(-90);
      //botController->wallFollow();
      botController->sweep(4,140);
      
    }
    if(input == 'a'){
    }

    if(input == 'd'){
    }
    if(input == 's'){
    }
  }
  wait_us(100000);
}


