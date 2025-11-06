#include <mbed.h>
#include <DigitalOut.h>
#include <PwmOut.h>
#ifndef MOTOR_INCLUDE
#define MOTOR_INCLUDE

class Motor{
  private:
  PinName _dirPin; //direction controlling pin
  PinName _powPin; //power contolling pin
  bool _inverse; //if the motor is facing in the opposite direction, reverses movement direction
  float _dutyCycle; //PWM duty cycle
  int _frequency_kHz; //PWM frequency
  


  public:
  mbed::DigitalOut _dirOut;
  mbed::PwmOut _powOut;

  Motor(PinName dirPin, PinName powPin, bool inverse);

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