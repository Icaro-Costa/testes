#include <Arduino.h>

#include "../include/config.h"
#include "../include/ventoinha.h"

// Canal PWM da ventoinha
const int canalVentoinha = 2;

void setupVentoinha() {
  // Conecta o pino ao canal PWM
  ledcAttachPin(FAN_PIN, canalVentoinha);
  // Configura o canal com 1000Hz de frequência e 16 bits de resolução
  ledcSetup(canalVentoinha, 1000, 16);
}

void setVentoinha(int velocidade) {
  // Garante que o valor está entre 0 e 65535
  velocidade = constrain(velocidade, 0, 65535);
  // Escreve o valor no canal PWM
  ledcWrite(canalVentoinha, velocidade);
}