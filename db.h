#ifndef PERSISTENT_H_
#define PERSISTENT_H_


#include "eeprom.h"


#define DBADDR  0x0


struct vi {
    float v;
    float i;
};


struct db {
    bool dirty;

    struct vi change;
    struct vi discharge;
};


void
db_load(struct db *d) {
    EEPROM.get(DBADDR, *d);
}


void
db_commit(struct db *d) {
    d->dirty = false;
    EEPROM.put(DBADDR, *d);
    eeprom_crc_store();
}


#endif  // PERSISTENT_H_
