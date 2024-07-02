#include "Arduino_FreeRTOS.h"
#include "task.h"

#define LED1 7
#define LED2 8

/* Variáveis para armazenamento do handle das tasks */
//TaskHandle_t Tarefa1Handle = NULL;
//TaskHandle_t Tarefa2Handle = NULL;

/*protótipos das Tasks*/
void vTarefa1(void *pvParameters);
void vTarefa2(void *pvParameters);

void setup() {
  xTaskCreate(vTarefa1, "Tarefa1",128, NULL, 1, NULL);
  xTaskCreate(vTarefa2, "Tarefa2",128, NULL, 1, NULL);
  //vTaskStartScheduler();
}

void loop() {
//As funções são executadas nas tarefas
}

void vTarefa1(void *pvParameters){
  pinMode(LED1, OUTPUT);
  while(1)  {
    digitalWrite(LED1,!digitalRead(LED1));
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void vTarefa2(void *pvParameters){
  pinMode(LED2, OUTPUT);
  while(1)  {
    digitalWrite(LED2,!digitalRead(LED2));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
