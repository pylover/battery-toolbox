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
#include <avr/interrupt.h>

#include "common.h"
#include "lcd2x16.h"
#include "acs712.h"
#include "thermistor.h"
#include "voltmeter.h"
#include "melody.h"
#include "menu.h"
#include "rotary.h"
#include "db.h"
#include "dialog.h"
#include "program.h"
#include "discharge.h"
#include "charge.h"


static struct menu_entry actions[] = {
    {"Charge", Charge::show},
    {"Discharge", Discharge::show},
};


#define MAXTEMP 100
#define MAXPOWER 60
#define VREF 4.8
#define MOSFET 9

#define RELAY_PIN 11
#define ON 0
#define OFF 1
#define RELAY(s) digitalWrite(RELAY_PIN, s)

#define BUZZER 6
#define BUZZ(t) \
    tone(BUZZER, 1000); \
    delay(t); \
    noTone(BUZZER)

static Menu menu("Main menu:", actions, ENTRYCOUNT(actions));
static struct db db;
static LCD2X16 lcd(13, 12, 8, 7, 5, 4);
static Rotary rotary;
static VoltMeter vmeter(A5, A0, K(44.2), K(13));
static ACS712 ammeter(A1, K(1.8), K(47));
static Thermistor heatsink(A2, THERMISTOR_100K_B3950, K(4.7));


ISR(PCINT1_vect) {
    if (PINC & (1 << PINC4)) {
        rotary.pushed();
    }
}


void
setup() {
    Serial.begin(115200);
    while (!Serial) {}

    analogReference(EXTERNAL);

    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, 0);

    pinMode(MOSFET, OUTPUT);
    digitalWrite(MOSFET, 0);

    pinMode(RELAY_PIN, OUTPUT);
    RELAY(OFF);

    ammeter.callibrate();

    /* Serial greeting */
    infoln();
    infoln(PROJECT);
    infoln(VVERSION);
    infoln();
}


void
loop() {
    struct menu_entry *prog;

    if (eeprom_crc_check()) {
        eeprom_format();
    }

    db_load();

    // /* Greeting */
    // Message::show(PROJECT, VVERSION, greeting_melody);

    while (true) {
        /* Main menu */
        prog = menu.show();

        /* Execute */
        prog->func();
    }
    while (true) {}
}
