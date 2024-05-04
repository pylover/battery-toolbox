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
#include "examine.h"
#include "discharge.h"
#include "charge.h"


static struct menu_entry actions[] = {
    {"Examine", Examine::show},
    {"Discharge", Discharge::show},
    {"Charge", Charge::show},
};


#define VREF 4.8
#define BUZZER 6
#define MOSFET 9
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
    while (!Serial);

    /* Serial greeting */
    infoln();
    infoln(PROJECT);
    infoln(VVERSION);
    infoln();

    analogReference(EXTERNAL);
    pinMode(BUZZER, OUTPUT);
    pinMode(MOSFET, OUTPUT);
    digitalWrite(BUZZER, 0);
    digitalWrite(MOSFET, 0);
    rotary.begin();
    lcd.begin();
    ammeter.callibrate();
}


void 
loop() {
    struct menu_entry *prog;

    if (eeprom_crc_check()) {
        eeprom_format();
    }
    
    db_load(&db);
    
    /* Greeting */
    Message::show(PROJECT, VVERSION, greeting_melody);

    while (true) {
        /* Main menu */
        prog = menu.show();

        /* Execute */
        prog->func();
    }
    while (true);
}
