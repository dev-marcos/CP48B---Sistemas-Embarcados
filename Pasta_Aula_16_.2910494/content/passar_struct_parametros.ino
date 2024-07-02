#include "Arduino_FreeRTOS.h"
#include "task.h"

#define LED1 7
#define LED2 8

typedef struct pisca_led
{
  uint16_t Tempo_ms;
  uint8_t pino;
} led_t;

led_t led1 = {500, LED1}; //LED1: delay 500ms (1Hz), pino 7
led_t led2 = {1000, LED2}; //LED2: delay 1000ms (0,5Hz), pino 8

/* Variáveis para armazenamento do handle das tasks*/
TaskHandle_t Tarefa1Handle = NULL;
TaskHandle_t Tarefa2Handle = NULL;

/*protítipos das Tasks*/
void vTarefa1(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  xTaskCreate(vTarefa1, "Tarefa1", 128, (void *)&led1, 1, &Tarefa1Handle);
  xTaskCreate(vTarefa1, "Tarefa2", 128, (void *)&led2, 1, &Tarefa2Handle);
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
