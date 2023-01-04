/*
 * FreeRTOS Esempio 01: un task per lampeggio led
 * 
 * Nota: nel file soc.h sono definiti i riferimenti ai due core della ESP32:
 *   #define PRO_CPU_NUM (0)
 *   #define APP_CPU_NUM (1)
 * 
 * Qui viene adoperata la APP_CPU
 * 
*/

#include <Arduino.h>

// indirizzo del led da accendere
const gpio_num_t pinLed = GPIO_NUM_23;

// task per il lampeggio del led su GPIO23
void toggleLed(void *parameters) {
  while(1) {
    digitalWrite(pinLed, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // portTICK_PERIOD_MS = num. di ticks al ms
    digitalWrite(pinLed, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // portTICK_PERIOD_MS = num. di ticks al ms    
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("FreeRTOS: lampeggio di un led da un task");

  pinMode(pinLed, OUTPUT);

  // creazione ed avvio del task
  xTaskCreatePinnedToCore(
    toggleLed,    // funzione da richiamare nel task
    "Toggle_LED", // nome del task (etichetta utile per debug)
    1024,         // dimensione in byte dello stack per le variabili locali del task (minimo 768 byte)
    NULL,         // puntatore agli eventuali parametri da passare al task
    1,            // priorità del task
    NULL,         // eventuale task handle per gestire il task da un altro task
    APP_CPU_NUM   // core su cui far girare il task
  );

  // da qui in poi il task viene mandato automaticamente in esecuzione ciclica,
  // nel porting di FreeRTOS fatto da Espressif NON è necessario esplicitare
  // il comando vTaskStartScheduler()
}

void loop() {
  // nel porting di Espressif, la loop() è eseguita in un task a priorità 1
}