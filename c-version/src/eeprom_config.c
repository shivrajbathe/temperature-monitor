#include "eeprom_config.h"
#include "hal_eeprom.h"
#include <string.h>

#define EEPROM_ADDR_REVISION    (0x0000U)
#define EEPROM_ADDR_SERIAL      (0x0001U)
#define EEPROM_SERIAL_LEN       (7U)        /* e.g. "ABC1234" */

bool eeprom_config_load(board_config_t *cfg)
{
    uint8_t rev = 0U;
    bool    ok  = true;

    /* Safe defaults first. */
    cfg->revision = HW_REV_A;
    memset(cfg->serial, 0, sizeof(cfg->serial));

    ok = ok && hal_eeprom_read(EEPROM_ADDR_REVISION, &rev, 1U);
    ok = ok && hal_eeprom_read(EEPROM_ADDR_SERIAL,
                               (uint8_t *)cfg->serial, EEPROM_SERIAL_LEN);
    if (!ok) {
        return false;
    }

    cfg->revision = (rev == 1U) ? HW_REV_B : HW_REV_A;
    cfg->serial[EEPROM_SERIAL_LEN] = '\0';
    return true;
}
