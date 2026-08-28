#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

/* Sampling period in microseconds (see requirement: sample every 100 us). */
#define SAMPLE_PERIOD_US        (100U)

/*
 * Canonical internal temperature unit: milli-degrees Celsius (m degC).
 * Fixed-point integers are used instead of floating point so the same
 * code runs on MCUs without an FPU and stays fully deterministic.
 */
typedef int32_t temp_mc_t;

/* Classification thresholds, expressed in milli-degrees Celsius. */
#define TEMP_CRIT_LOW_MC        (5000)      /*   5.0 degC */
#define TEMP_WARN_MC            (85000)     /*  85.0 degC */
#define TEMP_CRIT_HIGH_MC       (105000)    /* 105.0 degC */

typedef enum {
    HW_REV_A = 0,   /* 1.0 degC per digit  */
    HW_REV_B = 1    /* 0.1 degC per digit  */
} hw_revision_t;

typedef enum {
    LED_STATE_NORMAL = 0,   /* Green  */
    LED_STATE_WARNING,      /* Yellow */
    LED_STATE_CRITICAL      /* Red    */
} led_state_t;

#define HW_SERIAL_MAX_LEN       (16U)

typedef struct {
    hw_revision_t revision;
    char          serial[HW_SERIAL_MAX_LEN];
} board_config_t;

#endif /* CONFIG_H */
