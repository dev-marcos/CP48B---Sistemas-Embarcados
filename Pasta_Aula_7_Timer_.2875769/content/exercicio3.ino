#include <TimerOne.h>

#define LED0 7
#define BOTAO 2

void aciona_led();
void timer1segundo();

void setup() {  
  pinMode(LED0, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BOTAO), aciona_led, FALLING);
  Timer1.attachInterrupt(timer1segundo); 
  Timer1.stop();
}

void loop() {
}

void aciona_led (){
 Timer1.initialize(5000000);
 Serial.println("botao pressionado");
}

void timer1segundo (){
 Timer1.stop(); 
 digitalWrite(LED0, !digitalRead(LED0));
 Serial.println("LED acionado");
}
