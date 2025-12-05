#include "BotMap.h"





void BotMap::polarToCartesian(double distance, int theta){
    //_x = (int)(distance * cos((theta/180)*PI));
    //_y = (int)(distance * sin((theta/180)*PI));
}

void BotMap::posSet(float* xPos, float* yPos){
    _x = xPos;
    _y = yPos;
}



void BotMap::gridUpdate(float* distanceArrayX, float* distanceArrayY){
    //array length
    int getArrayLength = sizeof(distanceArrayX) / sizeof(distanceArrayX[0]);
    for(int i = 0; i < getArrayLength; i++){
        obstacleGrid[][]
    }
}
