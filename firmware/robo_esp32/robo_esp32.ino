#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth não está habilitado!
#endif

BluetoothSerial SerialBT;

// --- Lado Esquerdo (Ponte H Esquerda) ---
const int esquerdoPWMA = 4;   // D4 (Velocidade Frente Esquerda)[cite: 5]
const int esquerdoAIN1 = 25;  // D25 (Direção Frente Esquerda 1)[cite: 5]
const int esquerdoAIN2 = 26;  // D26 (Direção Frente Esquerda 2)[cite: 5]
const int esquerdoPWMB = 2;   // D2 (Velocidade Trás Esquerda)[cite: 5]
const int esquerdoBIN1 = 32;  // D32 (Direção Trás Esquerda 1)[cite: 5]
const int esquerdoBIN2 = 33;  // D33 (Direção Trás Esquerda 2)[cite: 5]

// --- Lado Direito (Ponte H Direita) ---
const int direitoPWMA = 18;   // D18 (Velocidade Frente Direita)[cite: 5]
const int direitoAIN1 = 27;   // D27 (Direção Frente Direita 1)[cite: 5]
const int direitoAIN2 = 14;   // D14 (Direção Frente Direita 2)[cite: 5]
const int direitoPWMB = 5;    // D5 (Velocidade Trás Direita)[cite: 5, 6]
const int direitoBIN1 = 12;   // D12 (Direção Trás Direita 1)[cite: 5, 6]
const int direitoBIN2 = 13;   // D13 (Direção Trás Direita 2)[cite: 5, 6]

const int freq = 30000;       // Frequência PWM (30 kHz)[cite: 5]
const int resolucao = 8;      // Resolução de 8 bits (0 a 255)[cite: 5]
int velocidadeAtual = 200;    // Velocidade padrão dos motores[cite: 5]

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Robo_Bluetooth"); // Nome do Bluetooth modificado

  // Configuração dos pinos digitais de direção
  pinMode(esquerdoAIN1, OUTPUT);
  pinMode(esquerdoAIN2, OUTPUT);
  pinMode(esquerdoBIN1, OUTPUT);
  pinMode(esquerdoBIN2, OUTPUT);
  pinMode(direitoAIN1, OUTPUT);
  pinMode(direitoAIN2, OUTPUT);
  pinMode(direitoBIN1, OUTPUT);
  pinMode(direitoBIN2, OUTPUT);[cite: 6]

  // Inicializa o PWM para cada pino de velocidade (ESP32 Core v3.x)[cite: 6]
  ledcAttach(esquerdoPWMA, freq, resolucao);[cite: 6]
  ledcAttach(esquerdoPWMB, freq, resolucao);[cite: 6]
  ledcAttach(direitoPWMA, freq, resolucao);[cite: 6]
  ledcAttach(direitoPWMB, freq, resolucao);[cite: 6]

  pararCarrinho();[cite: 6]
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();[cite: 6]
    switch (comando) {
      case 'F': case 'f': moverFrente(velocidadeAtual); break;[cite: 6]
      case 'B': case 'b': moverTras(velocidadeAtual); break;[cite: 6]
      case 'L': case 'l': virarEsquerda(velocidadeAtual); break;[cite: 6]
      case 'R': case 'r': virarDireita(velocidadeAtual); break;[cite: 6]
      case 'S': case 's': pararCarrinho(); break;[cite: 6]
      // Atalhos de velocidade pelo aplicativo
      case '1': velocidadeAtual = 100; break; // Lento[cite: 6]
      case '2': velocidadeAtual = 180; break; // Médio[cite: 6]
      case '3': velocidadeAtual = 255; break; // Máximo[cite: 6]
    }
  }
}

// --- Funções de Movimento ---
void moverFrente(int v) {
  ledcWrite(esquerdoPWMA, v); ledcWrite(esquerdoPWMB, v);[cite: 6]
  ledcWrite(direitoPWMA, v); ledcWrite(direitoPWMB, v);[cite: 6]

  // Esquerda para frente[cite: 6]
  digitalWrite(esquerdoAIN1, LOW); digitalWrite(esquerdoAIN2, HIGH);[cite: 6]
  digitalWrite(esquerdoBIN1, LOW); digitalWrite(esquerdoBIN2, HIGH);[cite: 6]

  // Direita para frente[cite: 6]
  digitalWrite(direitoAIN1, HIGH); digitalWrite(direitoAIN2, LOW);[cite: 6]
  digitalWrite(direitoBIN1, HIGH); digitalWrite(direitoBIN2, LOW);[cite: 6]
}

void moverTras(int v) {
  ledcWrite(esquerdoPWMA, v); ledcWrite(esquerdoPWMB, v);[cite: 6, 7]
  ledcWrite(direitoPWMA, v); ledcWrite(direitoPWMB, v);[cite: 6, 7]

  // Esquerda para trás[cite: 7]
  digitalWrite(esquerdoAIN1, HIGH); digitalWrite(esquerdoAIN2, LOW);[cite: 7]
  digitalWrite(esquerdoBIN1, HIGH); digitalWrite(esquerdoBIN2, LOW);[cite: 7]

  // Direita para trás[cite: 7]
  digitalWrite(direitoAIN1, LOW); digitalWrite(direitoAIN2, HIGH);[cite: 7]
  digitalWrite(direitoBIN1, LOW); digitalWrite(direitoBIN2, HIGH);[cite: 7]
}

void virarEsquerda(int v) {
  ledcWrite(esquerdoPWMA, v); ledcWrite(esquerdoPWMB, v);[cite: 7]
  ledcWrite(direitoPWMA, v); ledcWrite(direitoPWMB, v);[cite: 7]

  // Esquerda para trás (reverso)[cite: 7]
  digitalWrite(esquerdoAIN1, LOW); digitalWrite(esquerdoAIN2, HIGH);[cite: 7]
  digitalWrite(esquerdoBIN1, LOW); digitalWrite(esquerdoBIN2, HIGH);[cite: 7]

  // Direita para frente[cite: 7]
  digitalWrite(direitoAIN1, LOW); digitalWrite(direitoAIN2, HIGH);[cite: 7]
  digitalWrite(direitoBIN1, LOW); digitalWrite(direitoBIN2, HIGH);[cite: 7]
}

void virarDireita(int v) {
  ledcWrite(esquerdoPWMA, v); ledcWrite(esquerdoPWMB, v);[cite: 7]
  ledcWrite(direitoPWMA, v); ledcWrite(direitoPWMB, v);[cite: 7]

  // Esquerda para frente[cite: 7]
  digitalWrite(esquerdoAIN1, HIGH); digitalWrite(esquerdoAIN2, LOW);[cite: 7]
  digitalWrite(esquerdoBIN1, HIGH); digitalWrite(esquerdoBIN2, LOW);[cite: 7]

  // Direita para trás (reverso)[cite: 7]
  digitalWrite(direitoAIN1, HIGH); digitalWrite(direitoAIN2, LOW);[cite: 7]
  digitalWrite(direitoBIN1, HIGH); digitalWrite(direitoBIN2, LOW);[cite: 7]
}

void pararCarrinho() {
  ledcWrite(esquerdoPWMA, 0); ledcWrite(esquerdoPWMB, 0);[cite: 7]
  ledcWrite(direitoPWMA, 0); ledcWrite(direitoPWMB, 0);[cite: 7]

  digitalWrite(esquerdoAIN1, LOW); digitalWrite(esquerdoAIN2, LOW);[cite: 7]
  digitalWrite(esquerdoBIN1, LOW); digitalWrite(esquerdoBIN2, LOW);[cite: 7]
  digitalWrite(direitoAIN1, LOW); digitalWrite(direitoAIN2, LOW);[cite: 7]
  digitalWrite(direitoBIN1, LOW); digitalWrite(direitoBIN2, LOW);[cite: 7]
}
