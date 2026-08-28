#ifndef SAMPLING_H
#define SAMPLING_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Time-critical sampling path.
 *
 * sampling_isr() is the body of the 100 us timer interrupt. It is kept
 * deliberately small (read ADC, publish sample) so the sampling instant
 * has very low jitter. All heavier work (conversion, classification,
 * LED update) runs later in the main loop via sampling_get_latest().
 */
void sampling_init(void);
void sampling_isr(void);
bool sampling_get_latest(uint16_t *raw);

#endif /* SAMPLING_H */
