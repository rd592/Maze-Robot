#include "PID.h"


PID:: PID(){}

double PID:: computePID(double inp) {
  currentTime = millis();
  elapsedTime = (double)(currentTime - previousTime);

  error = setPoint - inp;
  cumError += error * elapsedTime;
  rateError = (error - lastError) / elapsedTime;

  double out = Kp * error + Ki * cumError + Kd * rateError;

  // --- Prevent integral wind-up ---
  out = constrain(out, 0, 255);  

  lastError = error;
  previousTime = currentTime;

  out = (out-127.5)/255; //returns out between -1 and 1
  return out;
}