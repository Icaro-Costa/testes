#include <Arduino.h>
#include "../include/pid.h"

// Variáveis do PID
float p = 0, i = 0, d = 0, lastError = 0;

// Ganhos do PID (extern para serem modificados via BT)
extern float Kp;
extern float Ki;
extern float Kd;
extern bool limiter;
extern int integralLimit;

int calcularPID(int erro) {
  p = erro;
  i = i + erro;
  if (limiter) {
    i = constrain(i, -integralLimit, integralLimit); // Limita o termo integral
  }
  d = erro - lastError;
  lastError = erro;

  return (Kp * p) + (Ki * i) + (Kd * d);
}
