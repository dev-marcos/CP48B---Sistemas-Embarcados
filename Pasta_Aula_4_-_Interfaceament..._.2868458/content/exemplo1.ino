#define LED0 7
#define botao 2

//Variaveis para analise do switch
bool nivel_passado_botao = HIGH;     // nivel passado de entrada do botao
bool nivel_antes_debounce_botao = HIGH;   // nivel antes de entrar na rotina

// variaveis para contagem de tempo
// ultimo valor de tempo (em millis) em que ocorreu o ultimo pressionamento (ou ruido) no botao
unsigned long ultima_mudanca_switch_entrada = 0;  
// delay ate estabilizar o pressionamento (quando pressiona e quando solta)
int debounce_Delay = 100;

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(LED0, OUTPUT);
}

void loop() {
  // leitura do estado atual do botao
  bool leitura_atual = digitalRead(botao);
  // verifica se o estado do botao alterou (pode ser por pressionamento ou por ruido)
  if (leitura_atual != nivel_antes_debounce_botao) {
    // reseta a variavel de tempo
    ultima_mudanca_switch_entrada = millis();
  }

  // atualiza o ultimo nivel com a leitura atual
  nivel_antes_debounce_botao = leitura_atual;

  // O sinal de entrada devera ficar estavel por no minimo "debounce_Delay"
  if ((millis() - ultima_mudanca_switch_entrada) > debounce_Delay) {
    // caso o switch tenha alterado o nivel, ele atualiza a variavel
    if (leitura_atual != nivel_passado_botao) {
      nivel_passado_botao = leitura_atual;
      // altera o estado do LED quando pressiona o botão (LOW)
      if (nivel_passado_botao == HIGH) {
        digitalWrite(LED0, !digitalRead(LED0));
        //Coloque aqui o que deve acontecer/setar flags
      }
    }
  }
}
