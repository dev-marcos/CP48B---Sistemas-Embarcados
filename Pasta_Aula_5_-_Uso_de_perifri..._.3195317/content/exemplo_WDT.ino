#include <avr/wdt.h>
 
#define Botao 2
#define LED 9
 
void setup() {
  wdt_enable(WDTO_4S); //Configura o WDT para 4 S
  pinMode (Botao, INPUT_PULLUP);
  pinMode (LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Iniciando o microcontrolador"); 
  digitalWrite (LED, HIGH);
}
 
void loop() {
  wdt_reset(); //Reinicia o WDT
  //O WDT não será reiniciado caso o botão permaneça
  //pressionado por mais de 4 segundos, isso fará o WDT
  //resetar o microcontrolador

  delay(200);
  digitalWrite (LED, LOW);
  
  while (digitalRead(Botao) == LOW) {
  //não faz nada, apenas mantém a execução travada
  }
}
