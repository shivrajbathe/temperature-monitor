#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>

/* Hardware abstraction for the temperature ADC channel. */
void     hal_adc_init(void);
uint16_t hal_adc_read_raw(void);   /* most recent raw conversion result */

#endif /* HAL_ADC_H */
