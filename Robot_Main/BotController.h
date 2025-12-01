#ifndef BOT_INCLUDE
#define BOT_INCLUDE

#include <mbed.h>
#include "MotorController.h"
#include "USSensor.h"
#include "ServoController.h"
#include "IRSensor.h"
 

 //states for fsm
 //still needs implementation of find pos for setup, map follow, and an end state
enum BotState{
  STATE_STOP = 0,
  STATE_FORWARD,
  STATE_BACKWARD,
  STATE_LEFT,
  STATE_RIGHT,
  STATE_ALIGN,
  STATE_MAP
};
extern BotState currentState;


//this class is the overall abstracted bot controller. Contains all functions needed for bot control
class BotController{

private:
MotorController* _motorController;
USSensor* _us1;
IRSensor* _ir1;
IRSensor* _ir2;
ServoController* _servo;

//store current sensor data
float _us1Out;
float _ir1Out;
float _ir2Out;

float* _distanceArray; //dont hard code 10

bool _stopped=0; //true if too close to an object in front
bool _noWall = 0; //used to ensure the robot turns back to the forward direction after trying to find a wall

const int _stoppingDistance = 10;//stopping distance in cm
const int _wallDetectionDistance = 15; //max distance a wall is detected on right side

float _xPos = 0;
float _yPos = 0;

float _speed = 1.0f; //robot move speed



// FSM transition bools
bool _mapping = 0, _blockedFront = 0, _blockedRight = 0, _aligning = 0;


public:
BotController(MotorController* motorController, USSensor* USSensor, IRSensor* ir1, IRSensor* ir2, ServoController* servo);

void setSpeed(float speed);

void sensorUpdate();

void turnAngle(float angle); 

//controls the speed of the movement
//1 for forward, 0 for no movement,-1 for backward
void speed(float speed); 

//forward movement by given distance (cm) at given speed (0-1)
void moveDistance(float distance);

//move until an obstacle is detected at distance.
void moveUntil(float distance, float stoppingDistance);

void wallAlign();

void wallFollow();

void sweep(int points, int angleRange); //performs a servo sweep, updates distanceArray pointer

void map(); //map area in front of robot


void fsmStart(); //finite state machine start function

};



#endif