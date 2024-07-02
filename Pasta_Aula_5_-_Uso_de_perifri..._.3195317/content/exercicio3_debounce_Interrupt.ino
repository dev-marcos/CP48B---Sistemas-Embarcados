#define LED0 7
#define botao 2

//Variaveis para analise do switch
bool nivel_passado_botao = HIGH;     // nivel passado de entrada do botao
bool nivel_antes_debounce_botao = HIGH;   // nivel antes de entrar na rotina
unsigned long ultima_mudanca_switch_entrada = 0;  
int debounce_Delay = 100;
int contagem = 4;
bool botao_pressionado=false;

void botao_int();

void setup() {
  pinMode(botao, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(botao), botao_int, FALLING);
  pinMode(LED0, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(botao_pressionado==true){
    bool leitura_atual = digitalRead(botao);
    if (leitura_atual != nivel_antes_debounce_botao) {
      ultima_mudanca_switch_entrada = millis();
    }
    nivel_antes_debounce_botao = leitura_atual;

    if ((millis() - ultima_mudanca_switch_entrada) > debounce_Delay) {
      if (leitura_atual != nivel_passado_botao) {
        nivel_passado_botao = leitura_atual;
        if (nivel_passado_botao == LOW) {
          contagem = contagem-1;
          Serial.println(contagem);
          botao_pressionado=false;
          attachInterrupt(digitalPinToInterrupt(botao), botao_int, FALLING);
          //Coloque aqui o que deve acontecer/setar flags.
        }
      }
    }
    if(contagem==0){
      digitalWrite(LED0, !digitalRead(LED0));
      contagem=4;
    }
  }
}

void botao_int(){
    botao_pressionado=true;
    detachInterrupt(digitalPinToInterrupt(botao));
}
