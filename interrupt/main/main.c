#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define INPUT_PIN 0
#define LED_PIN 2

int state = 0;
QueueHandle_t interputQueue;

void IRAM_ATTR gpio_interrupt_handler(void *args)
{
    xQueueSendFromISR(interputQueue, &args, NULL);
}

void gpio_interrupt_init(gpio_num_t gpio_num, gpio_int_type_t edge)
{
    gpio_config_t io_conf;
    io_conf.intr_type = edge;
    io_conf.pin_bit_mask = (1ULL << gpio_num);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    io_conf.pull_down_en = 0;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(gpio_num, gpio_interrupt_handler, (void *)gpio_num);
}

void LED_Control_Task(void *params)
{
    int pinNumber, count = 0;
    while (true)
    {
        if (xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
        {
            state = !state;
            printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(INPUT_PIN));
            gpio_set_level(LED_PIN, state);
        }
    }
}

void app_main()
{
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_interrupt_init(INPUT_PIN, GPIO_INTR_NEGEDGE);
    interputQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(LED_Control_Task, "LED_Control_Task", 2048, NULL, 1, NULL);
}