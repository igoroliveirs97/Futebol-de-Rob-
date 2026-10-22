# 🤖 Futebol de Robô: Manual Prático de Montagem

![ESP32](https://img.shields.io/badge/Microcontrolador-ESP32-blue?style=flat-square&logo=espressif)
![Bluetooth](https://img.shields.io/badge/Comunica%C3%A7%C3%A3o-Bluetooth-brightgreen?style=flat-square&logo=bluetooth)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-success?style=flat-square)

> Documentação técnica oficial e guia prático para a construção e programação de um robô móvel com tração diferencial, arquitetura simétrica de controle de motores e comunicação via Bluetooth.

---

## 📋 Índice
- [Sobre o Projeto](#-sobre-o-projeto)
- [Arquitetura Eletrônica](#-arquitetura-eletrônica)
- [Materiais Utilizados](#-materiais-utilizados)
- [Passo a Passo da Montagem](#-passo-a-passo-da-montagem)
  - [Fase 1: Bateria e Chave Liga/Desliga](#fase-1-conectando-a-bateria-e-a-chave-ligadesliga)
  - [Fase 2: O Terra Comum (Obrigatório)](#fase-2-o-terra-comum-obrigatório)
  - [Fase 3: Alimentação Lógica e Força Bruta](#fase-3-alimentação-lógica-e-força-bruta)
  - [Fase 4: Conexão dos Motores](#fase-4-conectando-os-motores-frente-e-trás-independentes)
  - [Fase 5: Fiação de Comando (ESP32)](#fase-5-fiação-de-comando-controle-direto-pelo-esp32)
- [Código-Fonte (Firmware ESP32)](#-código-fonte-firmware-esp32)

---

## 🎯 Sobre o Projeto
O projeto **Futebol de Robô** tem como objetivo a criação de um carrinho robótico ágil e resistente, projetado para competições. Ele utiliza o conceito de **tração diferencial**, virando o chassi através do controle independente da velocidade e do sentido das rodas do lado esquerdo e do lado direito[cite: 2].

---

## ⚡ Arquitetura Eletrônica
Para garantir força máxima e estabilidade térmica (evitando o aquecimento do microcontrolador), a eletrônica do robô foi dividida em um sistema inteligente de energia e controle simétrico[cite: 2]:

* **🧠 O Cérebro (ESP32):** Processa o Bluetooth e envia os comandos de direção e velocidade[cite: 2].
* **⚙️ As Válvulas de Potência (Pontes H):** Utilizamos duas placas separadas (`TB6612FNG`), uma para o lado esquerdo e outra para o lado direito. Cada placa utiliza tanto o Canal A (motores da frente) quanto o Canal B (motores de trás) de forma individual ou sincronizada via código[cite: 2].
* **🔋 Isolamento de Energia:** O circuito conta com um regulador de 5V exclusivamente para a lógica (alimentando o ESP32 e o chip das Pontes H) e um regulador de 6V exclusivamente para a força bruta dos motores[cite: 2].

---

## 🧰 Materiais Utilizados

* **1x** Microcontrolador ESP32 (Placa principal com Bluetooth)[cite: 2]
* **2x** Placas Ponte H (`TB6612FNG`) – uma para o lado esquerdo, outra para o direito[cite: 2]
* **1x** Regulador de Tensão Step-Down (ajustado em **5V**) – protege e alimenta o ESP32 e a lógica[cite: 2]
* **1x** Regulador de Tensão Step-Down (ajustado em **6V**) – fornece torque máximo aos motores[cite: 2]
* **4x** Motores N20 com Caixa de Redução (motores compactos de alta tração: 2 à esquerda, 2 à direita)[cite: 2]
* **1x** Bateria (LiPo ou par de baterias 18650) com Case[cite: 2]
* **1x** Chave Push Button Ds-211 Com Trava (instalada no fio positivo para corte geral de energia)[cite: 2]
* **Diversos:** Fios, cabos jumper e chassi mecânico[cite: 2]

---

## 🛠️ Passo a Passo da Montagem

> [!NOTE]
> O que você fizer na Ponte H do lado esquerdo, fará de forma simétrica e idêntica na Ponte H do lado direito[cite: 3].

### Fase 1: Conectando a Bateria e a Chave Liga/Desliga
1. **Instalação da Chave:** Pegue o fio positivo (vermelho) que sai do Case da bateria e corte-o ao meio[cite: 3]. Conecte as duas pontas geradas nos terminais da chave liga/desliga[cite: 3]. Assim, quando a chave estiver em "OFF", a energia é cortada[cite: 3].
2. **Entrada nos Reguladores:** Pegue o fio positivo vindo da chave e ligue-o nas entradas positivas (`IN+`) dos dois reguladores de tensão (5V e 6V)[cite: 3].
3. **Terra da Bateria:** Pegue o fio negativo (preto) que sai do Case da bateria e ligue-o nas entradas negativas (`IN-`) de ambos os reguladores[cite: 3].

### Fase 2: O Terra Comum (Obrigatório)
> [!WARNING]
> Se o circuito não compartilhar o fio de retorno (negativo), as placas não se comunicam e a energia não flui corretamente[cite: 3]!

Junte em um **único ponto comum** todos os fios negativos (jumpers pretos) vindos de[cite: 3]:
* Saída `GND` do regulador de 5V[cite: 3]
* Saída `GND` do regulador de 6V[cite: 3]
* Um pino `GND` do ESP32[cite: 3]
* Pinos `GND` das duas placas Ponte H[cite: 3]

### Fase 3: Alimentação Lógica e Força Bruta
* **Energia Lógica (5V):** Conecte a saída positiva (`OUT+`) do Regulador de 5V nos seguintes pontos[cite: 3]:
  * Pino `VIN` do ESP32[cite: 3]
  * Pinos `VCC` e `STBY` da Ponte H Esquerda[cite: 3]
  * Pinos `VCC` e `STBY` da Ponte H Direita[cite: 3]
  > *Nota: A porta 3.3V do ESP32 deve permanecer vazia para proteger a placa contra sobrecarga térmica[cite: 3].*
* **Força dos Motores (6V):** Conecte a saída positiva (`OUT+`) do Regulador de 6V exclusivamente nos pinos `VM` das duas Pontes H[cite: 4].

### Fase 4: Conectando os Motores
* **Lado Esquerdo:**
  * *Motor da Frente:* Conecte nos bornes/parafusos `A01` e `A02`[cite: 4]
  * *Motor de Trás:* Conecte nos bornes/parafusos `B01` e `B02`[cite: 4]
* **Lado Direito:**
  * *Motor da Frente:* Conecte nos bornes/parafusos `A01` e `A02`[cite: 4]
  * *Motor de Trás:* Conecte nos bornes/parafusos `B01` e `B02`[cite: 4]

### Fase 5: Fiação de Comando (ESP32)
* **Ponte H Esquerda:**
  * ESP32 `D4` ➔ `PWMA` (Velocidade Frente Esq.)[cite: 4]
  * ESP32 `D25` ➔ `AIN1` (Direção Frente Esq. 1)[cite: 4]
  * ESP32 `D26` ➔ `AIN2` (Direção Frente Esq. 2)[cite: 4]
  * ESP32 `D2` ➔ `PWMB` (Velocidade Trás Esq.)[cite: 4]
  * ESP32 `D32` ➔ `BIN1` (Direção Trás Esq. 1)[cite: 4]
  * ESP32 `D33` ➔ `BIN2` (Direção Trás Esq. 2)[cite: 4]
* **Ponte H Direita:**
  * ESP32 `D18` ➔ `PWMA` (Velocidade Frente Dir.)[cite: 4]
  * ESP32 `D27` ➔ `AIN1` (Direção Frente Dir. 1)[cite: 4]
  * ESP32 `D14` ➔ `AIN2` (Direção Frente Dir. 2)[cite: 4]
  * ESP32 `D5` ➔ `PWMB` (Velocidade Trás Dir.)[cite: 5]
  * ESP32 `D12` ➔ `BIN1` (Direção Trás Dir. 1)[cite: 5]
  * ESP32 `D13` ➔ `BIN2` (Direção Trás Dir. 2)[cite: 5]

---

## 💻 Código-Fonte (Firmware ESP32)[cite: 5]

```cpp
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
  SerialBT.begin("Robo_Bluetooth"); // Nome do Bluetooth visível no app

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

  digitalWrite(esquerdoAIN1, LOW); digitalWrite(esquerdoAIN2, HIGH);[cite: 6]
  digitalWrite(esquerdoBIN1, LOW); digitalWrite(esquerdoBIN2, HIGH);[cite: 6]
  digitalWrite(direitoAIN1, HIGH); digitalWrite(direitoAIN2, LOW);[cite: 6]
  digitalWrite(direitoBIN1, HIGH); digitalWrite(direitoBIN2, LOW);[cite: 6]
}

void moverTras(int v) {
  ledcWrite(esquerdoPWMA, v); ledcWrite(esquerdoPWMB, v);[cite: 6, 7]
  ledcWrite(direitoPWMA, v); ledcWrite(direitoPWMB, v);[cite: 6, 7]

  digitalWrite(esquerdoAIN1, HIGH); digitalWrite(esquerdoAIN2, LOW);[cite: 7]
  digitalWrite(esquerdoBIN1, HIGH); digitalWrite(esquerdoBIN2, LOW);[cite: 7]
  digitalWrite(direitoAIN1, LOW); digitalWrite(direitoAIN2, HIGH);[cite: 7]
  digitalWrite(direitoBIN1, LOW); digitalWrite(direitoBIN2, HIGH);[cite: 7]
}

void virarEsquerda(int v) {
  ledcWrite(esquerdoPWMA, v); ledcWrite(esquerdoPWMB, v);[cite: 7]
  ledcWrite(direitoPWMA, v); ledcWrite(direitoPWMB, v);[cite: 7]

  digitalWrite(esquerdoAIN1, LOW); digitalWrite(esquerdoAIN2, HIGH);[cite: 7]
  digitalWrite(esquerdoBIN1, LOW); digitalWrite(esquerdoBIN2, HIGH);[cite: 7]
  digitalWrite(direitoAIN1, LOW); digitalWrite(direitoAIN2, HIGH);[cite: 7]
  digitalWrite(direitoBIN1, LOW); digitalWrite(direitoBIN2, HIGH);[cite: 7]
}

void virarDireita(int v) {
  ledcWrite(esquerdoPWMA, v); ledcWrite(esquerdoPWMB, v);[cite: 7]
  ledcWrite(direitoPWMA, v); ledcWrite(direitoPWMB, v);[cite: 7]

  digitalWrite(esquerdoAIN1, HIGH); digitalWrite(esquerdoAIN2, LOW);[cite: 7]
  digitalWrite(esquerdoBIN1, HIGH); digitalWrite(esquerdoBIN2, LOW);[cite: 7]
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
