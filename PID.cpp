#include "PID.h"


PID:: PID(){}

double PID::computePID(double inp, double setPoint)
{
    currentTime = millis();
    elapsedTime = (currentTime - previousTime) / 1000.0; // seconds

    error = setPoint - inp;

    // Integral with anti-windup
    //cumError += error * elapsedTime;
    //cumError = constrain(cumError, -iLimit, iLimit);

    // Derivative
    //rateError = (error - lastError) / elapsedTime;

    //double out = Kp * error + Kd * rateError;
    double out = Kp * error;

    // Limit output to -1, 1
    out = constrain(out, -1.0, 1.0);

    lastError = error;
    previousTime = currentTime;

    return out;
}