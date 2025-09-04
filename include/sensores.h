#ifndef SENSORES_H
#define SENSORES_H

// Inicializa os sensores QTR
void setupSensores();

// Realiza o processo de calibração dos sensores
void calibrarSensores();

// Lê a posição da linha e retorna um valor
int lerPosicaoLinha();

// Verifica se o marcador de fim de pista foi detectado
bool checarMarcadorFim();

#endif
