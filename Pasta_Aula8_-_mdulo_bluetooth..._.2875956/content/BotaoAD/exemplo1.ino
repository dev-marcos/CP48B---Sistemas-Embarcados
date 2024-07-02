#define entrada_analogica A0

int leitura = 0;
int x = 0;

void setup() {                
  Serial.begin(9600);
}

void loop() {
  leitura = analogRead(entrada_analogica);
  if (leitura>470 && leitura<550 && x==0){
    Serial.println("Botão 1 pressionado");
    x=1;
  }
  else if (leitura>950 && x==0){
    Serial.println("Botão 2 pressionado");
    x=1;
  }
  else if (leitura<50 && x==1){
    x=0;
  }
}
