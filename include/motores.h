#ifndef MOTORES_H
#define MOTORES_H

// Inicializa os pinos e o PWM para os motores
void setupMotores();

// Define a velocidade e direção de cada motor
void setMotor(int pwmA, int pwmB);

#endif
