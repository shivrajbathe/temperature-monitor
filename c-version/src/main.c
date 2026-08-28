/*
 * PC demonstration driver.
 *
 * On real hardware the 100 us timer ISR runs sampling_isr() and the
 * main loop calls app_run_once() forever. On the PC there is no timer,
 * so the demo injects raw readings and invokes the ISR body directly,
 * exercising the exact same processing pipeline (per the task note that
 * ISR calls need not be functional in the PC demo).
 */
#include "app.h"
#include "sampling.h"
#include "hal_gpio.h"
#include "mock_adc.h"
#include "mock_gpio.h"
#include "mock_eeprom.h"
#include <stdio.h>

static const char *active_led(void)
{
    if (mock_gpio_get(GPIO_LED_RED))    { return "RED";    }
    if (mock_gpio_get(GPIO_LED_YELLOW)) { return "YELLOW"; }
    if (mock_gpio_get(GPIO_LED_GREEN))  { return "GREEN";  }
    return "NONE";
}

static void feed(uint16_t raw)
{
    mock_adc_set_raw(raw);
    sampling_isr();      /* emulates the 100 us timer interrupt */
    app_run_once();      /* main-loop processing step */
    printf("  raw=%-6u -> LED=%s\n", raw, active_led());
}

int main(void)
{
    /* --- Rev-A run: 1.0 degC per digit --- */
    mock_eeprom_set_config(0U, "ABC1234");
    app_init();
    printf("-- Rev-A demo (1.0 degC per digit) --\n");
    feed(20);    /*  20.0 degC -> GREEN        */
    feed(84);    /*  84.0 degC -> GREEN        */
    feed(85);    /*  85.0 degC -> YELLOW       */
    feed(105);   /* 105.0 degC -> RED (high)   */
    feed(3);     /*   3.0 degC -> RED (low)    */

    /* --- Rev-B run: 0.1 degC per digit --- */
    printf("\n");
    mock_eeprom_set_config(1U, "XYZ9876");
    app_init();
    printf("-- Rev-B demo (0.1 degC per digit) --\n");
    feed(200);   /*  20.0 degC -> GREEN        */
    feed(900);   /*  90.0 degC -> YELLOW       */
    feed(1100);  /* 110.0 degC -> RED (high)   */
    feed(30);    /*   3.0 degC -> RED (low)    */

    return 0;
}
