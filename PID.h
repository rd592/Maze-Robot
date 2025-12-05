#ifndef PID_INCLUDE
#define PID_INCLUDE

#include <mbed.h>


class PID{

// --- PID constants (tune these for your system) ---
double Kp = 0.15f;
//double Ki = 0.0;
double Kd = 0.5f;

// --- PID variables ---
unsigned long currentTime, previousTime;
double elapsedTime;
double error, lastError;
double input, output;
double cumError, rateError;


public:

PID();
double computePID(double inp, double setPoint);

} ;


#endif 