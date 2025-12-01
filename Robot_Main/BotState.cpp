#include "BotState.h"

/*

BotState::BotState(BotController* bot):
  _bot(bot)
{}


void BotState::fsmStart(){


  switch(currentState){
    //from stop, can go to mapping, moving, turn left, turn right, or stay in stop
    case STATE_STOP:
      _bot->speed(0.0f);
      //if mapping is true, go to mapping state
      if(_mapping){
        currentState = STATE_MAP;
      }
      //if aligning, go to aligning state
      else if(_aligning){
        currentState = STATE_ALIGN;
      }
      //logic for if the robot is blocked
      else if(_blockedFront && _blockedRight){
        //if blocked from right and front, turn left
        currentState = STATE_LEFT;
      }
      //if no wall on right, turn right
      else if(!_blockedRight){
        currentState = STATE_RIGHT;
      }
      else if(!_blockedFront){
        currentState = STATE_FORWARD;

      }
      
      break;

    //from forward, can go to stop
    case STATE_FORWARD:
      _bot->speed(_bot._speed);

      //stop if changing state, or blocked, or if no wall on right
      if(_aligning || _mapping || _blockedFront || !_blockedRight){
        currentState = STATE_STOP;
      }

      break;

    //after moving backwards once, go back to stop state. currently not implemented
    case STATE_BACKWARD:
      _bot->speed(-_speed);
      currentState = STATE_STOP;
      break;
    
    //after turning, go back to stop
    case STATE_LEFT:
      _bot->turnAngle(-90);
      currentState = STATE_STOP;
      break;

    case STATE_RIGHT:
      _bot->turnAngle(90);
      currentState = STATE_STOP;
      break;
    
    case STATE_ALIGN:
      _bot->wallAlign();

      currentState = STATE_STOP;
      break;

    case STATE_MAP:
      _bot->map();

      currentState = STATE_STOP;
      break;
  }
}

*/