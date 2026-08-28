#include "hal_eeprom.h"
#include "mock_eeprom.h"
#include <string.h>

static uint8_t s_rev            = 0U;
static char    s_serial[16]     = "ABC1234";

void hal_eeprom_init(void) { /* nothing to do for the mock */ }

bool hal_eeprom_read(uint16_t addr, uint8_t *buf, size_t len)
{
    if ((addr == 0x0000U) && (len >= 1U)) {
        buf[0] = s_rev;
        return true;
    }
    if (addr == 0x0001U) {
        memset(buf, 0, len);
        memcpy(buf, s_serial, (len < sizeof(s_serial)) ? len : sizeof(s_serial));
        return true;
    }
    return false;
}

void mock_eeprom_set_config(uint8_t revision, const char *serial)
{
    s_rev = revision;
    strncpy(s_serial, serial, sizeof(s_serial) - 1U);
    s_serial[sizeof(s_serial) - 1U] = '\0';
}
