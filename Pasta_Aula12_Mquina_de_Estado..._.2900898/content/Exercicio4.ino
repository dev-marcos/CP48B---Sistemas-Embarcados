#define LED1  4
#define LED2  5
#define LED3  6
#define LED4  7
#define Botao 2
#define Botao_Stop 3

//variaveis globais:
int tempo_delay = 300;

void (*PonteiroDeFuncao)(); //ponteiro de função da máquina de estados. Ele aponta sempre para a função da máquina de estados que deve ser executada
void (*temp)(); // posição da máquina de estados antes do stop
 
//prototypes:
void ESTADO_1(void);    //função que representa o estado inicial da máquina de estados
void ESTADO_2(void);   
void ESTADO_3(void);   
void ESTADO_4(void);
void ESTADO_5(void);

void Botao_ISR();

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(Botao, INPUT_PULLUP);
  pinMode(Botao_Stop, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Botao_Stop), Botao_ISR, CHANGE);
  Serial.begin(9600);
} 

void Botao_ISR(){
         if (!digitalRead(Botao_Stop)){
            temp = PonteiroDeFuncao;
            PonteiroDeFuncao = ESTADO_5;}
         else{
            PonteiroDeFuncao = temp;}       
}



void ESTADO_1(void)
{
                digitalWrite(LED1, HIGH);
                digitalWrite(LED2, LOW);
                digitalWrite(LED3, LOW);
                digitalWrite(LED4, LOW);
                if(digitalRead(Botao)){
                    PonteiroDeFuncao = ESTADO_2;}
                else
                    {PonteiroDeFuncao = ESTADO_4;}
}
 
void ESTADO_2(void)
{
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, HIGH);
                digitalWrite(LED3, LOW);
                digitalWrite(LED4, LOW);
                if(digitalRead(Botao)){
                    PonteiroDeFuncao = ESTADO_3;}
                else
                    {PonteiroDeFuncao = ESTADO_1;}
}
 
void ESTADO_3(void)
{
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, LOW);
                digitalWrite(LED3, HIGH);
                digitalWrite(LED4, LOW);
                if(digitalRead(Botao)){
                    PonteiroDeFuncao = ESTADO_4;}
                else
                    {PonteiroDeFuncao = ESTADO_2;}
}
 
void ESTADO_4(void)
{
                  digitalWrite(LED1, LOW);
                  digitalWrite(LED2, LOW);
                  digitalWrite(LED3, LOW);
                  digitalWrite(LED4, HIGH);
                  if(digitalRead(Botao)){
                      PonteiroDeFuncao = ESTADO_1;}
                  else
                      {PonteiroDeFuncao = ESTADO_3;}
}

void ESTADO_5(void)
{
                digitalWrite(LED1, LOW);
                digitalWrite(LED2, LOW);
                digitalWrite(LED3, LOW);
                digitalWrite(LED4, LOW);
}

void loop() 
{
        PonteiroDeFuncao = ESTADO_1; //aponta para o estado inicial. Nunca esquecer de informar um estado inicial (senão, nesse caso em específico, pode haver um erro fatal / hard fault).
      
        while(1)
        {
            if (Serial.available()>1){
            tempo_delay = Serial.parseInt();
            Serial.println(tempo_delay);}
           
           (*PonteiroDeFuncao)();    //chama a função apontada pelo ponteiro de função (logo, chama o estado corrente)
           delay(tempo_delay);
        }
}
