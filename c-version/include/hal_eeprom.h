#ifndef HAL_EEPROM_H
#define HAL_EEPROM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Hardware abstraction for the I2C configuration EEPROM. */
void hal_eeprom_init(void);
bool hal_eeprom_read(uint16_t addr, uint8_t *buf, size_t len);

#endif /* HAL_EEPROM_H */
