#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

byte red = 2;
byte blue = 8;

void TaskBlinkRed(void* pvParameters);
void TaskBlinkBlue(void* pvParameters);
void TaskPrint(void* pvParameters);

void setup() {
    Serial.begin(9600);

    xTaskCreate(
        TaskBlinkRed,
        "Task1",
        128,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        TaskBlinkBlue,
        "Task2",
        128,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        TaskPrint,
        "Task3",
        128,
        NULL,
        1,
        NULL
    );

    vTaskStartScheduler();
}

void loop() {
}

void TaskBlinkRed(void* pvParameters) {
    pinMode(red, OUTPUT);
    while(1) {
        digitalWrite(red, HIGH);
        vTaskDelay(200/portTICK_PERIOD_MS);
        digitalWrite(red, LOW);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void TaskBlinkBlue(void* pvParameters) {
    pinMode(blue, OUTPUT);
    while(1) {
        digitalWrite(blue, HIGH);
        vTaskDelay(500/portTICK_PERIOD_MS);
        digitalWrite(blue, LOW);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void TaskPrint(void* pvParameters) {
    int counter = 0;
    while(1) {
        counter++;
        Serial.println(counter);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}