#ifndef MOCK_GPIO_H
#define MOCK_GPIO_H
#include "hal_gpio.h"
#include <stdbool.h>
/* Test hook: reads the last state written to a mocked LED line. */
bool mock_gpio_get(gpio_led_t led);
#endif /* MOCK_GPIO_H */
