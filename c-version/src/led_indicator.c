#include "led_indicator.h"
#include "hal_gpio.h"

void led_indicator_init(void)
{
    hal_gpio_init();
    hal_gpio_write(GPIO_LED_GREEN,  false);
    hal_gpio_write(GPIO_LED_YELLOW, false);
    hal_gpio_write(GPIO_LED_RED,    false);
}

void led_indicator_set(led_state_t state)
{
    /* Mutually exclusive: the three writes keep a single LED lit. */
    hal_gpio_write(GPIO_LED_GREEN,  state == LED_STATE_NORMAL);
    hal_gpio_write(GPIO_LED_YELLOW, state == LED_STATE_WARNING);
    hal_gpio_write(GPIO_LED_RED,    state == LED_STATE_CRITICAL);
}
