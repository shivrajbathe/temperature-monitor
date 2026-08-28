#include "temp_classifier.h"

led_state_t temp_classify(temp_mc_t t)
{
    /* Critical takes precedence: below 5 degC or at/above 105 degC. */
    if ((t < TEMP_CRIT_LOW_MC) || (t >= TEMP_CRIT_HIGH_MC)) {
        return LED_STATE_CRITICAL;
    }
    /* Warning: at/above 85 degC and below 105 degC. */
    if (t >= TEMP_WARN_MC) {
        return LED_STATE_WARNING;
    }
    /* Normal: 5 degC up to below 85 degC. */
    return LED_STATE_NORMAL;
}
