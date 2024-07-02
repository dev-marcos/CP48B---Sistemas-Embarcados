#include <Servo.h>
int x,posicao;
Servo myservo; // cria o objeto

void setup() {
  myservo.attach(9);
  Serial.begin(9600);  
}

void loop() {
  if (Serial.available()>0){
  x = Serial.parseInt();
  }
  if(x==1){
  posicao = posicao+20;
  if (posicao>180) {posicao=180;}
    Serial.println(posicao);
  }
  if(x==2){
  posicao = posicao-20;
  if (posicao<0) {posicao=0;}
    Serial.println(posicao);
  }
  if(x==3){
  posicao = 0;
  Serial.println(posicao);
  }
  if(x==4){
  posicao = 180;
  Serial.println(posicao);
  }
  x=0;
  myservo.write(posicao);                
  delay(100);                 
}
