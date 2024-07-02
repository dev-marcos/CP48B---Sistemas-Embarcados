#define LED1  4
#define LED2  5
#define LED3  6
#define LED4  7
#define Botao 2

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(Botao, INPUT_PULLUP);
} 

void (*PonteiroDeFuncao)(); //ponteiro de função da máquina de estados. Ele aponta sempre para a função da máquina de estados que deve ser executada
 
//prototypes:
void ESTADO_1(void);    //função que representa o estado inicial da máquina de estados
void ESTADO_2(void);   
void ESTADO_3(void);   
void ESTADO_4(void); 

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

void loop() 
{
        PonteiroDeFuncao = ESTADO_1; //aponta para o estado inicial. Nunca esquecer de informar um estado inicial (senão, nesse caso em específico, pode haver um erro fatal / hard fault).
      
        while(1)
        {
           (*PonteiroDeFuncao)();    //chama a função apontada pelo ponteiro de função (logo, chama o estado corrente)
           delay(300);
        }
}
