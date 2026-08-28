#include "temp_sensor.h"

/* Scale factor: raw digit -> milli-degrees Celsius. Default is Rev-A. */
static int32_t s_scale_mc_per_digit = 1000;

void temp_sensor_init(hw_revision_t revision)
{
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
