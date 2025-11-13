using namespace mbed;
#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include <InterruptIn.h>

#include "Motor.h"
#include "MotorController.h"
#include "IRSensor.h"
#include "USSensor.h"
#include "ServoController.h"

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


  //rtos::Thread mapThread; //will be used for us sensor movement and mapping to prevent processor starvation


  //mbed::I2C* i2c;
  char cmd[2];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  //set up motor objects and controller
  motorA = new Motor(ADir, APow, 1, AEnc);
  motorB = new Motor(BDir, BPow, 0, BEnc);
  controller = new MotorController(motorA, motorB);

  //set motors to idle
  controller->turn(0);
  controller->move(0);
  controller->encoderUpdate();

  //set up IR sensors
  ir1 = new IRSensor(0xEE, 0b0001); //IR bus 0
  ir2 = new IRSensor(0xEE, 0b0010); //IR bus 1


  //set up US Sensor
  us1 = new USSensor(TrigEcho);

  servo = new ServoController(servoSig, TrigEcho);
  
  //servo sweep needs multithreading as it uses a lot of wait functions
  //servo->sweep(8, 140);

  //myServo.attach(servoSig);
  
 
}


int temp2 = 0;
void loop() {

    controller->printEncoder();

    wait_us(10000);
   
    us1Out = us1->getOutput();

    //Serial.println("us1 output:");
    //Serial.println(us1Out);
    

    ir1Out = ir1->getOutput();

    //Serial.println("ir1 output:");
    //Serial.println(ir1Out);
    

    ir2Out = ir2->getOutput();

   // Serial.println("ir2 output:");
   // Serial.println(ir2Out);
    

  
  //reset motor movement
  controller->move(0);

  //wasd movement
  if(Serial.available() >0){


    char input = Serial.read();
    if(input == 'w'){
      controller->turn(0);
      controller->move(0.8f);
      
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
  
  
}


