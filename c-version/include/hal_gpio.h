#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdbool.h>

typedef enum {
    GPIO_LED_GREEN = 0,
    GPIO_LED_YELLOW,
    GPIO_LED_RED,
    GPIO_LED_COUNT
} gpio_led_t;

void hal_gpio_init(void);
void hal_gpio_write(gpio_led_t led, bool on);

#endif /* HAL_GPIO_H */
