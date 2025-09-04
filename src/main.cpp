#include <Arduino.h>
#include "config.h"
#include "motores.h"
#include "sensores.h"
#include "pid.h"
#include "bluetooth.h"
#include "ventoinha.h" // Inclui a nova biblioteca

#include <BluetoothSerial.h>

// Variáveis de estado e parâmetros
unsigned long startMakerChecker = 39500L;
unsigned long initialTime;
int marginError = 20;

// Parâmetros PID 
float Kp = 0.3;
float Ki = 0.0001;
float Kd = 3.5;
int maxSpeed = 100;
int integralLimit = 200;
bool limiter = false;
bool fimDePista = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  setupMotores();
  setupSensores();
  setupVentoinha(); // Inicializa a ventoinha
  setupBluetooth();
  aguardarComandosBluetooth();

  calibrarSensores();
  delay(2000);
  initialTime = millis();
}

void loop() {
  if (fimDePista) {
    setMotor(0, 0);
    setVentoinha(0); // Desliga a ventoinha no fim da pista
    return;
  }

  // Checa o marcador de fim de pista
  if (checarMarcadorFim()) {
    fimDePista = true;
    
    extern BluetoothSerial SerialBT;
    SerialBT.println("Linha de chegada detectada!");
    float time = (millis() - initialTime) / 1000.0;
    SerialBT.print(">> Tempo: ");
    SerialBT.print(time);
    SerialBT.println(" segundos");
    return;
  }

  // Lê a posição da linha e ajusta a velocidade
  int position = lerPosicaoLinha();
  int error = map(position, 0, MAX_POSITION, -1000, 1000);
  int pid_adjust = calcularPID(error);
  int lSpeed = constrain(maxSpeed + pid_adjust, -maxSpeed, maxSpeed);
  int rSpeed = constrain(maxSpeed - pid_adjust, -maxSpeed, maxSpeed);

  // Aplica a velocidade aos motores
  setMotor(lSpeed, rSpeed);

  // Exemplo de uso da ventoinha
  // A velocidade da ventoinha pode ser fixa ou variável
  // Aqui, um exemplo simples: a ventoinha liga com 50% da força
  setVentoinha(32768); // ~50% de 65535
}