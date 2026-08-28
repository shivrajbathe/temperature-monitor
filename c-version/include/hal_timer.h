#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <stdint.h>

typedef void (*timer_cb_t)(void);

/*
 * Configure a periodic hardware timer that fires every 'period_us'
 * microseconds and invokes 'cb' from interrupt context.
 */
void hal_timer_init(uint32_t period_us, timer_cb_t cb);
void hal_timer_start(void);

#endif /* HAL_TIMER_H */
