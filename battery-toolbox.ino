#include <avr/interrupt.h>

#include "lcd2x16.h"
#include "acs712.h"
#include "thermistor.h"
#include "voltmeter.h"
#include "melody.h"

#include "common.h"
#include "menu.h"
#include "rotary.h"


static LCD2X16 lcd(13, 12, 8, 7, 5, 4);
static Rotary rotary;


#include "dialog.h"
#include "examine.h"
#include "discharge.h"


static float greeting_melody[] = {
    nE4, dQ,
    nA4, dQ,
    nC5, dQ,
    nB4, dQ,
    nA4, dH,
    nC5, dHQ,
    nA4, dQ,
    nB4, dQ,
    nA4, dQ,
    nF4, dQ,
    nG4, dQ,
    nE4, dH,
    0, 0
};


static struct menu_entry actions[] = {
    {"Examine", Examine::show},
    {"Discharge", Discharge::show},
    {"foo", NULL},
    {"bar", NULL},
    {"quux", NULL},
};


static Menu menu("Main menu:", actions, ENTRYCOUNT(actions));

static VoltMeter voltmeter(A0, 16.384 / (float)1024);
static ACS712 ammeter(A1, 48 / (float)1024);
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
    infoln();
    infoln(PROJECT);
    infoln(VVERSION);
    infoln();

    rotary.begin();
    lcd.begin();

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(BUZZER, OUTPUT);

    analogReference(EXTERNAL);
}


void 
loop() {
    struct menu_entry *prog;

    /* Greeting */
    Message::show(PROJECT, VVERSION, greeting_melody);
    // Greeting::modal();

    // /* PWM DAC */
    // int duty = 0;
    // while (true) {
    //     analogWrite(10, duty); 
    //     analogWrite(9, duty); 
    //     Serial.println(duty);
    //     /* for PWM frequency of ~62K Hz */
    //     TCCR1B = TCCR1B & B11100000 | B00001001; 
    //     
    //     duty = IntegerInputDialog::show("Duty Cycle:", 0, 255, duty);
    // }

    while (true) {
        /* Main menu */
        prog = menu.show();

        /* Execute */
        prog->func();
    }
    while (true);
}
