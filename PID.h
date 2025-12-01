#ifndef PID_INCLUDE
#define PID_INCLUDE

#include <mbed.h>


class PID{

// --- PID constants (tune these for your system) ---
double Kp = 2.0;
double Ki = 5.0;
double Kd = 1.0;

// --- PID variables ---
unsigned long currentTime, previousTime;
double elapsedTime;
double error, lastError;
double input, output, setPoint;
double cumError, rateError;


public:

PID();
double computePID(double inp);

} ;


#endif 