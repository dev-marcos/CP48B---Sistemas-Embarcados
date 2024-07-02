#define entrada_analogica A0


int x = 0;

void setup() {                
  Serial.begin(9600);
}

void loop() {
  long leitura = 0;
  for(int i=0;i<100;i++)
  {
    leitura = leitura+analogRead(entrada_analogica);
  }
    leitura = leitura/100;
  
  if (leitura>720 && leitura<800 && x==0){
    Serial.println("Ambos botões pressionados");
    x=1;
  }
  else if (leitura>580 && leitura<640 && x==0){
    Serial.println("Botão 2 pressionado");
    x=1;
  }
  else if (leitura>470 && leitura<510 && x==0){
    Serial.println("Botão 1 pressionado");
    x=1;
  }
  else if (leitura<50 && x==1){
    x=0;
  }
}
