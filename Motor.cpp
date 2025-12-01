#include "Motor.h"
using namespace mbed;
 

Motor::Motor(PinName dirPin, PinName powPin, bool inverse, PinName encoderPin, float adjust):
  _dirPin(dirPin), _powPin(powPin), _dirOut(dirPin), _powOut(powPin), _inverse(inverse), _encoderPin(encoderPin), _encInt(encoderPin), _adjust(adjust)
{
  _frequency_kHz = 2; //intitial values
  //setFrequency(_frequency_kHz);
  _dutyCycle = 0;
  setDutyCycle(_dutyCycle);
}

//encoder counting
void Motor::countPulse(){
  if(_dutyCycle >0){
    if(_dirOut == 1)
      _encCount++;
    else
      _encCount--;
  }

}

//interrupt start function
void Motor::encUpdate(){
  _encCount = 0;
  _encInt.rise(callback(this, &Motor::countPulse)); //updates the encoder counter on every rising edge
  _encInt.fall(callback(this, &Motor::countPulse)); //updates the encoder counter on every falling edge
}

//return encoder output adjusting for inversion
long int Motor::getEncoder(){
  if(_inverse){
    return -_encCount;
  }
  else{
    return _encCount; 
  }
  
}

void Motor::setDirPin(PinName dirPin){
    _dirPin = dirPin;
}
void Motor::setPowPin(PinName powPin){
  _powPin = powPin;
}
void Motor::setInverse(bool inverse){
  _inverse = inverse;
}


PinName Motor::getDirPin(){
  return _dirPin;
}
PinName Motor::getPowPin(){
  return _powPin;
}
bool Motor::getInverse(){
  return _inverse;
}

//0 for back 1 for forward movement of the motor
void Motor::setDirection(bool direction){
  bool dirTemp = direction;
  if(_inverse){
      _dirOut = !dirTemp;
  }
  else{
    _dirOut = dirTemp;
  }

}

//sets the duty cycle of the PWM output. float between 0 and 1
void Motor::setDutyCycle(float dutyCycle){
  if(dutyCycle*_adjust > 1){
    _dutyCycle = 1;
  }
  else if(dutyCycle*_adjust < 0){
    _dutyCycle = 0;
  }
  else{
    _dutyCycle = dutyCycle*_adjust;
  }
  _powOut.write(_dutyCycle);
}
//set the frequency of the PWM output. Capped between 1 kHz and 100kHz
void Motor::setFrequency(int frequency_kHz){
  if(frequency_kHz >100){
    _frequency_kHz = 100;
  }
  else if(frequency_kHz < 1){
    _frequency_kHz = 1;
  }
  else{
    _frequency_kHz = frequency_kHz;
  }

  int period = (1/_frequency_kHz) * 1000;
  Serial.println(period);
  _powOut.period_ms(period);
}

      
    
