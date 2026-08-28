#include "hal_timer.h"

/*
 * PC stub. There is no real timer on the PC, so the ISR is invoked
 * manually by the demo. On target this module would configure a
 * hardware timer peripheral to fire every 'period_us' and call 'cb'.
 */
static timer_cb_t s_cb     = 0;
static uint32_t   s_period = 0U;

void hal_timer_init(uint32_t period_us, timer_cb_t cb)
{
    s_period = period_us;
    s_cb     = cb;
}

void hal_timer_start(void) { /* no-op on PC */ }
