#ifndef LED_INDICATOR_H
#define LED_INDICATOR_H

#include "config.h"

void led_indicator_init(void);
void led_indicator_set(led_state_t state);   /* exactly one LED active */

#endif /* LED_INDICATOR_H */
