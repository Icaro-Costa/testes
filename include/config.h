#ifndef CONFIG_H
#define CONFIG_H

#define BT_NAME "LinePRO"

// --- Pinos ---
#define PIN_BUTTON 0
#define SENSOR_R4 35 // Sensor lateral para detectar marcador

// Pinos da Ponte H (Driver dos Motores)
#define ENA 23 // PWM Motor A (Esquerdo)
#define IN1 21
#define IN2 22

#define ENB 5  // PWM Motor B (Direito)
#define IN3 18
#define IN4 19

#define STANDBY 17 // Pino de ativação dos motores

// Pino da Ventoinha
#define FAN_PIN 12 

// --- Sensores de Linha ---
const uint8_t SENSOR_COUNT = 8;
const long MAX_POSITION = (SENSOR_COUNT - 1) * 1000;
const bool LINE_BLACK = false; // Define se a linha a ser seguida é preta ou branca

#endif