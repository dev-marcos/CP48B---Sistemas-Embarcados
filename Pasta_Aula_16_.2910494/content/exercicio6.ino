#include "Arduino_FreeRTOS.h"
#include "task.h"

#define LED1 7
#define LED2 8
#define LED3 9
#define BOTAO 2

typedef struct pisca_led
{
  uint16_t Tempo_ms;
  uint8_t pino;
} led_t;

led_t led1 = {500, LED1}; //LED1: delay 500ms (1Hz), pino 7
led_t led2 = {1000, LED2}; //LED2: delay 1000ms (0,5Hz), pino 8
led_t led3 = {100, LED3}; //LED3: delay 100ms (5Hz), pino 9

/* Variáveis para armazenamento do handle das tasks*/
TaskHandle_t Tarefa1Handle = NULL;
TaskHandle_t Tarefa2Handle = NULL;
TaskHandle_t Tarefa3Handle = NULL;

/*protítipos das Tasks*/
void vTarefa1(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  xTaskCreate(vTarefa1, "Tarefa1", 128, (void *)&led1, 1, &Tarefa1Handle);
  xTaskCreate(vTarefa1, "Tarefa2", 128, (void *)&led2, 1, &Tarefa2Handle);
  xTaskCreate(vTarefa3, "Tarefa3", 128, NULL, 1, &Tarefa3Handle);
  pinMode(BOTAO, INPUT_PULLUP);
}

void loop()
{
}

void vTarefa1(void *pvParameters) // Mesma função chamada com 2 tarefas diferentes
{
  led_t *led = (led_t *)pvParameters; //faz a leitura da struct passada
  pinMode(led->pino, OUTPUT);         //configura pino como saída
  while (1)
  {
    Serial.println("Piscando o LED no pino: " + String(led->pino));
    digitalWrite(led->pino, !digitalRead(led->pino));
    vTaskDelay(pdMS_TO_TICKS(led->Tempo_ms));
    }
}

void vTarefa3(void *pvParameters)
{
  int debouncingContagem = 0;
  int x = 0;
  int estado_anterior = HIGH;
  while(1)
  {
    if(digitalRead(BOTAO) == LOW)
    {
      debouncingContagem++;
      if(debouncingContagem >= 10 && x == 0 && estado_anterior == HIGH) {
        debouncingContagem = 0;
         Serial.println("Suspendendo tarefa 1");
         vTaskSuspend(Tarefa1Handle);
         digitalWrite(LED1,LOW);
         x=1;
         estado_anterior = LOW;
      }
      else if (debouncingContagem >= 10 && x == 1 && estado_anterior == HIGH){
         debouncingContagem = 0;
         Serial.println("Reativando tarefa 1");
         vTaskResume(Tarefa1Handle);
         digitalWrite(LED1,LOW);
         x=0;
         estado_anterior = LOW;
      }
    }
    else
    {
      debouncingContagem = 0;
      estado_anterior = HIGH;
    }
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}
