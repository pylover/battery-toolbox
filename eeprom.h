/*
Copyright (c) 2024, Vahid Mardani <vahid.mardani@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation  and/or other materials provided with the distribution.
3. Neither the names of the copyright holders nor the names of any
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef EEPROM_H_
#define EEPROM_H_


#include <Arduino.h>
#include <EEPROM.h>


#define EEPROM_METADATA_SIZE (sizeof(unsigned long) * 2)
#define EEPROM_MAGIC 0x48484848


unsigned long
eeprom_crc() {
    const unsigned long crc_table[16] = {
        0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
        0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
        0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
        0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
    };

    unsigned long crc = ~0L;

    for (int i = 0; i < EEPROM.length() - EEPROM_METADATA_SIZE; ++i) {
        crc = crc_table[(crc ^ EEPROM[i]) & 0x0f] ^ (crc >> 4);
        crc = crc_table[(crc ^ (EEPROM[i] >> 4)) & 0x0f] ^ (crc >> 4);
        crc = ~crc;
    }

    return crc;
}


void
eeprom_crc_store() {
    unsigned long crc = eeprom_crc();
    int addr = EEPROM.length() - EEPROM_METADATA_SIZE;
    EEPROM.put(addr, EEPROM_MAGIC);
    EEPROM.put(addr + sizeof(unsigned long), crc);
}


void
eeprom_format() {
    Serial.print("Formatting EEPROM (");
    Serial.print(EEPROM.length());
    Serial.print(" bytes) ");
    for (int i = 0; i < EEPROM.length(); ++i) {
        Serial.write('.');
        EEPROM.write(i, 0);
    }
    Serial.println(" done.");
    eeprom_crc_store();
}


int
eeprom_crc_check() {
    unsigned long crc = eeprom_crc();
    unsigned long magic;
    unsigned long storedcrc = 0;
    int addr = EEPROM.length() - EEPROM_METADATA_SIZE;
    EEPROM.get(addr, magic);
    EEPROM.get(addr + sizeof(unsigned long), storedcrc);
    if ((crc != storedcrc) || (magic != EEPROM_MAGIC)) {
        Serial.println("Error: EEPROM CRC/Magic mismatch");
        return -1;
    }
    Serial.println("EEPROM CRC OK");
    return 0;
}


#endif  // EEPROM_H_

