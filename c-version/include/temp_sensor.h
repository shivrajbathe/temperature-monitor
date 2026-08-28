#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include "config.h"
#include <stdint.h>

/*
 * Revision-aware sensor conversion. temp_sensor_init() selects the
 * scaling for the active hardware revision (Rev-A or Rev-B), and
 * temp_sensor_convert() maps a raw digit reading to the canonical
 * milli-degrees Celsius unit. temp_sensor_filter() applies the 5% reading
 * hysteresis. Only one revision is active per boot.
 */
void      temp_sensor_init(hw_revision_t revision);
temp_mc_t temp_sensor_convert(uint16_t raw);
temp_mc_t temp_sensor_filter(temp_mc_t temperature_mc);

#endif /* TEMP_SENSOR_H */
