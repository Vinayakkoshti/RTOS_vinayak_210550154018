

// make task periodic with 2 sec

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int count =0 ;
TaskHandle_t Handler,Handler2;
TickType_t xTicksToWait=2000 / portTICK_PERIOD_MS; 
TimeOut_t xTimeOut;
void Task_1(void *argument);
void Task_2(void *argument);

void app_main(void)
{
    xTaskCreate(Task_1,"TASK1",2048,NULL,2,&Handler);
    xTaskCreate(Task_2,"TASK2",2048,NULL,3,&Handler2);
}

void Task_1(void *argument)
{
    while(1)
    {
        printf("IN task_1\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS );
    }
}

//task 2 will come at every 2 seconds that the periodicity
void Task_2(void *argument)
{
    while(1)
    {
    vTaskSetTimeOutState( &xTimeOut );  // save time stamp 
     printf("IN task_2\n");
        while( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) != pdFALSE) // add time stamp with defined time 
        {
             /* Timed out before the wanted number of bytes were available, exit the
            loop. */
            break;
        }
     ulTaskNotifyTake( pdTRUE, xTicksToWait );//same as counting semaphore , wakes up task on defined time
    }
 }