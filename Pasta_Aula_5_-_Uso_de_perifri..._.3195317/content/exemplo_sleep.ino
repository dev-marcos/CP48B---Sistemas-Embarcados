// Biblioteca sleep
#include <avr/sleep.h>

#define botao 2

// Funções
void soneca();
void acordar();

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino ligado");
  pinMode(botao, INPUT_PULLUP);
}

void loop() {
  Serial.println("Microcontrolador ativo");
  delay(10000);
  soneca();
}

void soneca() {
  Serial.println("Ativando modo sleep");
  delay(50);
  attachInterrupt(digitalPinToInterrupt(botao), acordar, LOW );
  //Seleciona o tipo de sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  //Habilita o sleep, mas ainda não entra no modo sleep
  sleep_enable();
  //Entra no modo sleep, o código para nesse ponto
  sleep_cpu();
}

void acordar() {
  //Desativa o modo sleep
  sleep_disable();
  //Desativa a interrupção para evitar que essa função seja executada desnecessariamente
  detachInterrupt(digitalPinToInterrupt(botao));
  Serial.println("Modo sleep desativado");
  delay(50);
}
