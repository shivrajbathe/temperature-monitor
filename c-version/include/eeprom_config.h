#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

#include "config.h"
#include <stdbool.h>

/*
 * Load the board configuration (revision + serial) from EEPROM.
 * On failure 'cfg' is left in a safe default (Rev-A, empty serial)
 * and false is returned so the caller can enter a safe state.
 */
bool eeprom_config_load(board_config_t *cfg);

#endif /* EEPROM_CONFIG_H */
