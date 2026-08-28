#ifndef MOCK_EEPROM_H
#define MOCK_EEPROM_H
#include <stdint.h>
/* Test hook: preloads the mocked EEPROM contents. */
void mock_eeprom_set_config(uint8_t revision, const char *serial);
#endif /* MOCK_EEPROM_H */
