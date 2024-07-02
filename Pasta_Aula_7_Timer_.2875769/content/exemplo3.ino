#include <TimerOne.h>

int contador =0;

void timer1segundo();

void setup() {  
  Serial.begin(9600);
  Timer1.initialize(); 
  Timer1.setPeriod(1000000); // minimo 1 microsegundos e maximo 8,3 segundos
  Timer1.attachInterrupt(timer1segundo);
}

void loop() {
}

void timer1segundo (){
  contador++;
  Serial.println(contador);
}
