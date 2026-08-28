#ifndef TEMP_CLASSIFIER_H
#define TEMP_CLASSIFIER_H

#include "config.h"

/*
 * Pure classification of a temperature into an indicator state.
 * Priority order: critical (low or high) beats warning beats normal.
 */
led_state_t temp_classify(temp_mc_t temp_mc);

#endif /* TEMP_CLASSIFIER_H */
