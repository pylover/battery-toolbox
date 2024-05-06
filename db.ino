#include "db.h"


void
db_load() {
    EEPROM.get(DBADDR, db);
}


void
db_commit() {
    EEPROM.put(DBADDR, db);
    eeprom_crc_store();
}

