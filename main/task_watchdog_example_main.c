/* Task_Watchdog Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"

#define TWDT_TIMEOUT_S          2


/*
 * Macro to check the outputs of TWDT functions and trigger an abort if an
 * incorrect code is returned.
 */
#define CHECK_ERROR_CODE(returned, expected) ({                        \
            if(returned != expected){                                  \
                printf("TWDT ERROR\n");                                \
                abort();                                               \
            }                                                          \
})

static TaskHandle_t reset_wdt_task_handles;

void esp_task_wdt_isr_user_handler()
{   
    //Using this will cause reset when TWDT is triggered. Comment out this line to see the TWDT tigger message.
    // printf("******** user-defined  task_wdt_isr *********"); 
}


void app_main()
{
    printf("Initialize TWDT\n");
    // //Initialize or reinitialize TWDT
    CHECK_ERROR_CODE(esp_task_wdt_init(TWDT_TIMEOUT_S, false), ESP_OK);

    CHECK_ERROR_CODE(esp_task_wdt_add(NULL), ESP_OK);
    CHECK_ERROR_CODE(esp_task_wdt_status(NULL), ESP_OK);

    printf("Delay for 11 seconds, you will see TWDT being triggered every 2 seconds\n");
    vTaskDelay(pdMS_TO_TICKS(11000));   //Delay for 10 seconds

    printf("Start to reset TWDT every second, TWDT should not be triggered\n");
    for (int i=0;i<20;i++)
    {
        //reset the watchdog every second for 20 times
        printf("reset TWDT, count(%d)\n", i);
        CHECK_ERROR_CODE(esp_task_wdt_reset(), ESP_OK); //Comment this line to trigger a TWDT timeout
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    printf("reset TWDT complete, you will see TWDT being triggered every 2 seconds again.\n");
}
