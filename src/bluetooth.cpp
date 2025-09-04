#include <Arduino.h>
#include "../include/config.h"
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

String getElement(String data, int index);
double getNumber(String data, int index);
String getPrefix(String data);
String receiveBtMessage();
void printParameters();

extern float Kp, Ki, Kd;
extern int maxSpeed, marginError, integralLimit;
extern unsigned long startMakerChecker;
extern bool limiter;

// Inicia o Bluetooth
void setupBluetooth() {
  SerialBT.begin(BT_NAME);
  Serial.println("Dispositivo Bluetooth pronto!");
}

// Aguarda e processa comandos via Bluetooth
void aguardarComandosBluetooth() {
  SerialBT.println("Iniciando comunicacao BT...");
  String btMessage;
  String prefix = "";

  while (prefix != "end" && digitalRead(PIN_BUTTON) == HIGH) {
    btMessage = receiveBtMessage();
    if (btMessage.length() == 0) continue;

    prefix = getPrefix(btMessage);

    if (prefix == "pid") {
      Kp = getNumber(btMessage, 1);
      Ki = getNumber(btMessage, 2);
      Kd = getNumber(btMessage, 3);
    } else if (prefix == "spe") {
      maxSpeed = getNumber(btMessage, 1);
    } else if (prefix == "tim") {
      startMakerChecker = getNumber(btMessage, 1);
    } else if (prefix == "err") {
      marginError = getNumber(btMessage, 1);
    } else if (prefix == "pri") {
      printParameters();
    } else if (prefix == "lim") {
      limiter = !limiter;
      SerialBT.println(limiter ? "Limitador ativado!" : "Limitador desativado!");
    } else if (prefix != "end") {
      SerialBT.println("Comando nao existe!");
    }
  }

  printParameters();
  SerialBT.println("Iniciando Calibracao...");
  delay(500);
}

// Recebe uma mensagem via Bluetooth
String receiveBtMessage() {
  String message;
  char incomingChar;
  digitalWrite(LED_BUILTIN, HIGH);
  while (digitalRead(PIN_BUTTON) == HIGH) {
    if (SerialBT.available()) {
      incomingChar = SerialBT.read();
      if (incomingChar == '\n') break;
      message += String(incomingChar);
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
  message.trim();
  return message;
}

// Obtém o prefixo da mensagem
String getPrefix(String data) { return getElement(data, 0); }

// Obtém um número da mensagem
double getNumber(String data, int index) { return atof(getElement(data, index).c_str()); }

// Extrai um elemento da string
String getElement(String data, int index) {
  int found = 0;
  int start = 0;
  int end = -1;

  while (found <= index) {
    start = end + 1;
    end = data.indexOf(' ', start);
    if (end == -1) {
      if (found == index) {
        end = data.length();
        break;
      } else {
        return "";
      }
    }
    found++;
  }
  return data.substring(start, end);
}

// Imprime os parâmetros atuais
void printParameters() {
  SerialBT.println("Parametros configurados:");
  SerialBT.print(">> P: "); SerialBT.print(Kp, 4);
  SerialBT.print(" | I: "); SerialBT.print(Ki, 4);
  SerialBT.print(" | Kd: "); SerialBT.println(Kd, 4);
  SerialBT.print(">> Velocidade: "); SerialBT.println(maxSpeed);
  SerialBT.print(">> Atraso marcador: "); SerialBT.println(startMakerChecker);
  SerialBT.print(">> Margem Erro: "); SerialBT.println(marginError);
  SerialBT.print(">> Limitador: "); SerialBT.println(limiter);
}