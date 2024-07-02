 /*
 * Exemplo 2: Monitore um botão através de uma interrupção, de forma que ele envie para a tarefa 2, utilizando 
 * fila a informação, o valor “1” quando estiver em VCC, e “0” quando estiver em GND. A tarefa 1 é um LED em 1Hz.
 */

#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define LED1 7
#define BOTAO 2

/* Variáveis para armazenamento do handle das tasks */
TaskHandle_t xTarefa1Handle = NULL;
TaskHandle_t xTarefa2Handle = NULL;

/* Variáveis para armazenamento do handle das filas */
QueueHandle_t xFila;

/*protótipos das Tasks*/
void vTarefa1(void *pvParameters);
void vTarefa2(void *pvParameters);

void funcaoISR(){
    int valor;
    if (digitalRead(BOTAO)){
    valor=1;}
    else{
    valor=0;}
    xQueueSendFromISR(xFila, &valor, NULL);  
}

void setup() {
  Serial.begin(9600);
  pinMode(BOTAO, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BOTAO), funcaoISR, CHANGE);
  xFila = xQueueCreate(5, sizeof(int));
  xTaskCreate(vTarefa1, "Tarefa1",128, NULL, 2, &xTarefa1Handle);
  xTaskCreate(vTarefa2, "Tarefa2",128, NULL, 1, &xTarefa2Handle);
}

void loop() {
//As funções são executadas nas tarefas
}

void vTarefa1(void *pvParameters){
  pinMode(LED1, OUTPUT);
  while(1)
  {
    digitalWrite(LED1,!digitalRead(LED1));
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void vTarefa2(void *pvParameters){
  int valorrecebidofila;
  while(1)
  {
    xQueueReceive(xFila, &valorrecebidofila, portMAX_DELAY);
    Serial.println("Interrupcao recebida: " + String(valorrecebidofila));
  }
}
