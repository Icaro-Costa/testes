#include <Arduino.h>
#include "../include/motores.h"
#include "../include/config.h"

void setupMotores() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(STANDBY, OUTPUT);
  digitalWrite(STANDBY, HIGH); // Ativa os motores

  // Configura os canais PWM
  ledcSetup(0, 10000, 8); // Canal 0, freq 10kHz, resolução 8-bit
  ledcAttachPin(ENA, 0);   // Associa o pino ENA ao canal 0

  ledcSetup(1, 10000, 8); // Canal 1, freq 10kHz, resolução 8-bit
  ledcAttachPin(ENB, 1);   // Associa o pino ENB ao canal 1
}

void setMotor(int pwmA, int pwmB) {
  // Motor Esquerdo (A)
  if (pwmA > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    pwmA = -pwmA;
  }
  ledcWrite(0, constrain(pwmA, 0, 255));

  // Motor Direito (B)
  if (pwmB > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    pwmB = -pwmB;
  }
  ledcWrite(1, constrain(pwmB, 0, 255));
}
