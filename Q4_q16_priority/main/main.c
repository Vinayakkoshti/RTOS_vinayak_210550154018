#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t Handler,Handler2;
void Task_1(void *argument);
void Task_2(void *argument);

void app_main(void)
{
    xTaskCreate(Task_1,"TASK1",2048,NULL,10,&Handler);   // Priority 10
    xTaskCreate(Task_2,"TASK2",2048,NULL,20,&Handler2);  // Priority 20
}

void Task_1(void *argument)
{
    while(1)
    {
        printf("IN task_1 : Priority 10\n");
    }
}

void Task_2(void *argument)
{
    while(1)
    {
         printf("IN task_2 : Priority 20\n");
    }
 }