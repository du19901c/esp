#ifndef INPUT_IO_H
#define INPUT_IO_H
#include "esp_err.h"
#include "hal/gpio_types.h"

void gpio_interrupt_init(gpio_num_t gpio_num, gpio_int_type_t edge);


#endif