#ifndef MOTOR_INCLUDE
#define MOTOR_INCLUDE

#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#include <InterruptIn.h> 

class Motor{

  private:
  PinName _dirPin; //direction controlling pin
  PinName _powPin; //power contolling pin
  bool _inverse; //if the motor is facing in the opposite direction, reverses movement direction
  float _dutyCycle; //PWM duty cycle
  int _frequency_kHz; //PWM frequency
  float _adjust; //adjust for motor differences 
  

  PinName _encoderPin;

  public:
  mbed::DigitalOut _dirOut;
  mbed::PwmOut _powOut;

  long int _shaftRevs;
  long int _encCount; //encoder count 
  mbed::InterruptIn _encInt; //interrupt to update the encoder


  Motor(PinName dirPin, PinName powPin, bool inverse, PinName encoderPin, float adjust);


  void countPulse();  //encoder updater
  void encUpdate(); //interrupt call
  long int getEncoder();

  void setDirPin(PinName dirPin);
  void setPowPin(PinName powPin);
  void setInverse(bool inverse);

  PinName getDirPin();
  PinName getPowPin();
  bool getInverse();

void setDirection(bool direction);
void setDutyCycle(float dutyCycle);
void setFrequency(int frequency_kHz);

  
};

#endif