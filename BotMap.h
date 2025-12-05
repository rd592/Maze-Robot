#ifndef BOTMAP_INCLUDE
#define BOTMAP_INCLUDE

#include <mbed.h>
#include <math.h>



#define PI 3.1415926


//
// This class needs fleshing out next. Take sweep object positions from bot controller, add them to bot position, append them to map.
//

class BotMap{

private:



public:

//y is depth into the maze, x is distance across the maze in cm.
//bot starts at 0,0. x can be +,-, y can only be +
float* _x = 0; //x and y coordinates
float* _y = 0; 
float* _theta = 0; //angle of robot 

//maze size is 150*200cm
//need to measure maze size. 1cm precision is approach taken (x,y)
bool obstactleGrid[150][200];

//robots sensor frame, us sensor is offset 15cm from middle of wheels 
const float us1Frame[2] = {0, 15};
const float ir1Frame[2] = {7, 5.5f};
const float ir2Frame[2] = {7, 10};


void polarToCartesian(double distance, int theta);

void posSet(float* xPos, float* yPos);
void gridUpdate(float* distanceArrayX, float* distanceArrayY);


};


#endif