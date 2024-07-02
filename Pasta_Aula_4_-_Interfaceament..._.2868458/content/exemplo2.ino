
//Parametrizacao para a quantidade de botoes e LEDs
#define QUANTIDADE_BOTOES 2
const int botao[2] = {2, 3}; // Pinos especificos, nao é possivel parametrizar
const int LED[2] = {7, 8};    

//Declaracao das variaveis parametrizadas
bool nivel_passado_botao[QUANTIDADE_BOTOES] = {0};   // nivel atual de entrada do botao[i]
bool nivel_antes_debounce_botao[QUANTIDADE_BOTOES] = {0}; // nivel lido anteriormente no botao[i]
bool leitura_atual[QUANTIDADE_BOTOES]={0};
unsigned long ultima_mudanca_botao_entrada[QUANTIDADE_BOTOES] = {0};  
int debounce_Delay[QUANTIDADE_BOTOES] = {0};

void setup() {
for (int i = 0; i < QUANTIDADE_BOTOES; i++){
  //Inicializacao das variaveis parametrizadas
  nivel_passado_botao[i] = HIGH;     // nivel atual de entrada do botao[i]
  nivel_antes_debounce_botao[i] = HIGH;   // nivel lido anteriormente no botao[i]
  leitura_atual[i]=HIGH;
  ultima_mudanca_botao_entrada[i] = 0;  
  debounce_Delay[i] = 100;
    
  pinMode(botao[i], INPUT_PULLUP);
  pinMode(LED[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < QUANTIDADE_BOTOES; i++){
    // leitura do estado atual do botao[i]
    leitura_atual[i] = digitalRead(botao[i]);
    if (leitura_atual[i] != nivel_antes_debounce_botao[i]) {
      ultima_mudanca_botao_entrada[i] = millis();
    }
    nivel_antes_debounce_botao[i] = leitura_atual[i];
    // O sinal de entrada devera ficar estavel por no minimo "debounce_Delay[i]"
    if ((millis() - ultima_mudanca_botao_entrada[i]) > debounce_Delay[i]) {
      // caso o botao tenha alterado o nivel, ele atualiza a variavel
      if (leitura_atual[i] != nivel_passado_botao[i]) {
      nivel_passado_botao[i] = leitura_atual[i];

        // altera o estado do LED quando pressiona o botão (LOW)
        if (nivel_passado_botao[i] == LOW) {
           digitalWrite(LED[i], !digitalRead(LED[i]));
        }
      }
    }
  }
}
