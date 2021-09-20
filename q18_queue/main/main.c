#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t Handler,Handler2;
void Task_1(void *argument);
void Task_2(void *argument);

QueueHandle_t xQueue1;
UBaseType_t MAX_length = 5,y;

#define MAX sizeof(int)

int SendBuff[MAX],RecieveBuff[MAX];

int send = 20; 
void app_main(void)
{
    xQueue1 = xQueueCreate( MAX_length,sizeof(int));
    
    if(xQueue1==NULL)
    {
        printf("Failed to create queue!!!\n");
    }

    xTaskCreate(Task_1,"TASK1",2048,NULL,20,&Handler);
    xTaskCreate(Task_2,"TASK2",2048,NULL,10,&Handler2);
    
//    vQueueDelete(xQueue1);
}

void Task_1(void *argument)
{
    while(1)
    {
        printf("In task 1 : sending top screate over queue LOL !!!\n");
        send = send + 1;
        
        if( xQueueSend(xQueue1,(int*)&send,(TickType_t)10) != pdPASS )
        {
            printf("Failed to post the message, even after 10 ticks.\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task_2(void *argument)
{
    while(1)
    {
        if( xQueueReceive( xQueue1,(int *)RecieveBuff,(TickType_t)10) != pdPASS )
        {
            printf("Failed to Receive the message, even after 10 ticks.\n");
        }      
        else{
            printf("In task 2 got the msg : %d\n",RecieveBuff[0]);
        }
       
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
 }