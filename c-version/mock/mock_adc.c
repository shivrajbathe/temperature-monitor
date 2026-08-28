#include "hal_adc.h"
#include "mock_adc.h"

static uint16_t s_raw = 0U;

void     hal_adc_init(void)         { s_raw = 0U; }
uint16_t hal_adc_read_raw(void)     { return s_raw; }
void     mock_adc_set_raw(uint16_t raw) { s_raw = raw; }
