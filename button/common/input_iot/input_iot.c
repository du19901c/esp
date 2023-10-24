#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "input_iot.h"

input_callback_t input_callback = NULL;

IRAM_ATTR static void gpio_input_handler(void *arg)
{
    int gpio_num = (uint32_t)arg;
    // Handle GPIO interrupt here
    input_callback(gpio_num);
}

esp_err_t input_io_create(gpio_num_t gpio_num, interrupt_type_edge_t edge)
{
    esp_err_t err = ESP_OK;
    esp_rom_gpio_pad_select_gpio(gpio_num);
    gpio_set_direction(gpio_num, GPIO_MODE_INPUT);
    gpio_set_pull_mode(gpio_num, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(gpio_num, edge);
    err = gpio_install_isr_service(0);
    if (err != ESP_OK)
    {
        return err;
    }
    err = gpio_isr_handler_add(gpio_num, gpio_input_handler, (void *)gpio_num);
    return err;
}

int input_io_get_level(gpio_num_t gpio_num)
{
    return gpio_get_level(gpio_num);
}

esp_err_t input_set_callback(void *cb)
{
    // Implement this function to set a callback function for GPIO interrupts.
    // You can store the provided callback function pointer for future use.
    // Example: callback_function = (your_callback_function_type)cb;
    // ...
    input_callback = cb;
    return ESP_OK;
}
