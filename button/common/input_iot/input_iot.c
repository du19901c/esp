#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "input_iot.h"

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
