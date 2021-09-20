#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int count =0 ;
TaskHandle_t Handler,Handler2;
void Task_function(void *argument);
void Task_function2(void *argument);

void app_main(void)
{
    xTaskCreate(Task_function,"TASK",2048,NULL,2,&Handler);
    xTaskCreate(Task_function2,"TASK2",2048,NULL,3,&Handler2);
    /*int i = 0;
    while (1) {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }*/
}

void Task_function(void *argument)
{
    while(1)
    {
        count ++;
        printf("in Task : count :%d\n",count);    
        vTaskDelay(1000/portTICK_PERIOD_MS);
        if(count == 5)
        {
            //void vTaskDelete( TaskHandle_t xTask );
      //      vTaskDelete(Handler);
                vTaskSuspend(Handler);
        }
    }
}

void Task_function2(void *argument)
{
    while(1)
    {
        count++;
        printf("in Task 2 : count :%d\n",count);    
        vTaskDelay(1000/portTICK_PERIOD_MS);
        if(count==20)
        {
            vTaskResume(Handler);
        }
    }
 }