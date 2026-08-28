#include "app.h"
#include "config.h"
#include "eeprom_config.h"
#include "temp_sensor.h"
#include "temp_classifier.h"
#include "led_indicator.h"
#include "sampling.h"
#include "hal_timer.h"
#include <stdio.h>

static board_config_t s_cfg;

void app_init(void)
{
    led_indicator_init();

    /* 1. Read configuration from EEPROM over I2C. */
    if (!eeprom_config_load(&s_cfg)) {
        /* Safe state on configuration failure. */
        led_indicator_set(LED_STATE_CRITICAL);
        printf("[app] EEPROM read failed, entering safe state\n");
        return;
    }
    printf("[app] serial=%s revision=%s\n",
           s_cfg.serial, (s_cfg.revision == HW_REV_B) ? "Rev-B" : "Rev-A");

    /* 2. Configure revision-specific sensor scaling. */
    temp_sensor_init(s_cfg.revision);

    /* 3. Start the 100 us periodic timer that drives the sampling ISR. */
    sampling_init();
    hal_timer_init(SAMPLE_PERIOD_US, sampling_isr);
    hal_timer_start();
}

void app_run_once(void)
{
    uint16_t raw;
    if (sampling_get_latest(&raw)) {
        const temp_mc_t   t     = temp_sensor_convert(raw);
        const led_state_t state = temp_classify(t);
        led_indicator_set(state);
    }
}
