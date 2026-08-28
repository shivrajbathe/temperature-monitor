#ifndef MOCK_ADC_H
#define MOCK_ADC_H
#include <stdint.h>
/* Test hook: sets the raw value the mocked ADC returns next. */
void mock_adc_set_raw(uint16_t raw);
#endif /* MOCK_ADC_H */
