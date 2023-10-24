/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "input_iot.h"

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO 2
int s_ledstage;
void input_event_callback(int pin)
{
    if (pin == GPIO_NUM_0)
    {
        gpio_set_level(BLINK_GPIO, s_ledstage);
        s_ledstage =! s_ledstage;
    }
}
void app_main(void)
{
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    input_io_create(GPIO_NUM_0, HI_TO_LO);
    input_set_callback(input_event_callback);
}
