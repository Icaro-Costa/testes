#include <Arduino.h>
#include <QTRSensors.h>

#include "../include/config.h"
#include "../include/sensores.h"

#include <BluetoothSerial.h>


QTRSensors qtr;
uint16_t sensorValues[SENSOR_COUNT];

// Variáveis para o marcador de fim
extern unsigned long initialTime;
extern unsigned long startMakerChecker;

void setupSensores() {
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){ 32, 33, 25, 26, 27, 14, 12, 13 }, SENSOR_COUNT);
}

void calibrarSensores() {
  digitalWrite(LED_BUILTIN, HIGH);
  // Calibra até o botão ser pressionado
  while (digitalRead(PIN_BUTTON) == HIGH) {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);

  // Opcional: Imprimir valores de calibração via Bluetooth

    extern BluetoothSerial SerialBT;
    SerialBT.println("Valores minimos de calibracao:");
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      SerialBT.print(qtr.calibrationOn.minimum[i]);
      SerialBT.print(' ');
    }
    SerialBT.println();

    SerialBT.println("Valores maximos de calibracao:");
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      SerialBT.print(qtr.calibrationOn.maximum[i]);
      SerialBT.print(' ');
    }
    SerialBT.println();

}

int lerPosicaoLinha() {
  if (LINE_BLACK) {
    return qtr.readLineBlack(sensorValues);
  } else {
    return qtr.readLineWhite(sensorValues);
  }
}

bool checarMarcadorFim() {
  if (startMakerChecker < millis() - initialTime) {
    if (analogRead(SENSOR_R4) < 2000) {
      return true;
    }
  }
  return false;
}
