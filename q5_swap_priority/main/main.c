#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t Handler,Handler2;
void Task_1(void *argument);
void Task_2(void *argument);

UBaseType_t x,y;
int count = 0;
void app_main(void)
{
    xTaskCreate(Task_1,"TASK1",2048,NULL,20,&Handler);   // Priority 10
    xTaskCreate(Task_2,"TASK2",2048,NULL,10,&Handler2);  // Priority 20
}

void Task_1(void *argument)
{
    while(1)
    {
        count++;
        printf("IN task_1 : count : %d :: Priority : %d\n",count,uxTaskPriorityGet(Handler));
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        if(count==10)
        {
            x=uxTaskPriorityGet(Handler);
            vTaskPrioritySet( NULL, uxTaskPriorityGet(Handler2));
            vTaskPrioritySet(Handler2,x);
          //  vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void Task_2(void *argument)
{
    while(1)
    {
        printf("IN task_2  Priority : %d\n",uxTaskPriorityGet(Handler2));
       // vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
 }