#ifndef BOTMAP_INCLUDE
#define BOTMAP_INCLUDE

#include <mbed.h>
#include <math.h>



#define PI 3.1415926


//
// This class needs fleshing out next. Take sweep object positions from bot controller, add them to bot position, append them to map.
//
//
class BotMap{

private:



public:

//y is depth into the maze, x is distance across the maze in cm.
//bot starts at 0,0. x can be +,-, y can only be +
int _x = 0; //x and y coordinates
int _y = 0; 

//need to measure maze size. 1cm precision is probably best approach
bool obstactleGrid[50][50];


void polarToCartesian(double distance, int theta);


};


#endif