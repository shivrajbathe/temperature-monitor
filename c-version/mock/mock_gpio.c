#include "hal_gpio.h"
#include "mock_gpio.h"

static bool s_state[GPIO_LED_COUNT] = { false };

void hal_gpio_init(void)
{
    for (int i = 0; i < GPIO_LED_COUNT; ++i) {
        s_state[i] = false;
    }
}

void hal_gpio_write(gpio_led_t led, bool on)
{
    if (led < GPIO_LED_COUNT) {
        s_state[led] = on;
    }
}

bool mock_gpio_get(gpio_led_t led)
{
    return (led < GPIO_LED_COUNT) ? s_state[led] : false;
}
