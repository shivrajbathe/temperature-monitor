#include "temp_sensor.h"
#include <stdbool.h>

/* Scale factor: raw digit -> milli-degrees Celsius. Default is Rev-A. */
static int32_t s_scale_mc_per_digit = 1000;
static temp_mc_t s_filtered_temperature_mc;
static bool      s_filter_initialized;

void temp_sensor_init(hw_revision_t revision)
{
    s_filter_initialized = false;

    switch (revision) {
        case HW_REV_B:
            s_scale_mc_per_digit = 100;    /* 0.1 degC per digit */
            break;
        case HW_REV_A:
        default:
            s_scale_mc_per_digit = 1000;   /* 1.0 degC per digit */
            break;
    }
}

temp_mc_t temp_sensor_convert(uint16_t raw)
{
    return (temp_mc_t)((int32_t)raw * s_scale_mc_per_digit);
}

temp_mc_t temp_sensor_filter(temp_mc_t temperature_mc)
{
    int64_t difference_mc;
    int64_t hysteresis_mc;

    if (!s_filter_initialized) {
        s_filtered_temperature_mc = temperature_mc;
        s_filter_initialized = true;
        return temperature_mc;
    }

    difference_mc = (int64_t)temperature_mc - s_filtered_temperature_mc;
    if (difference_mc < 0) {
        difference_mc = -difference_mc;
    }

    hysteresis_mc = ((int64_t)s_filtered_temperature_mc < 0)
                  ? -(int64_t)s_filtered_temperature_mc
                  : (int64_t)s_filtered_temperature_mc;
    hysteresis_mc = (hysteresis_mc * 5) / 100;
    if (hysteresis_mc < 1) {
        hysteresis_mc = 1;
    }

    if (difference_mc > hysteresis_mc) {
        s_filtered_temperature_mc = temperature_mc;
    }

    return s_filtered_temperature_mc;
}
