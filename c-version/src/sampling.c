#include "sampling.h"
#include "hal_adc.h"

/*
 * Single-writer (ISR) / single-reader (main loop) exchange.
 * A 16-bit aligned load/store is atomic on the target MCU, so the raw
 * value itself needs no lock. 'volatile' prevents the compiler from
 * caching the values across the ISR / main-loop boundary.
 */
static volatile uint16_t s_raw_sample   = 0U;
static volatile bool     s_sample_ready = false;

void sampling_init(void)
{
    hal_adc_init();
    s_raw_sample   = 0U;
    s_sample_ready = false;
}

void sampling_isr(void)
{
    /* Minimal interrupt body: read and publish, nothing else. */
    s_raw_sample   = hal_adc_read_raw();
    s_sample_ready = true;
}

bool sampling_get_latest(uint16_t *raw)
{
    if (!s_sample_ready) {
        return false;
    }
    *raw           = s_raw_sample;
    s_sample_ready = false;
    return true;
}
