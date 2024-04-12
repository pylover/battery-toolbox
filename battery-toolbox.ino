#include <avr/interrupt.h>

#include "common.h"
#include "menu.h"
#include "display.h"
#include "rotary.h"
#include "dialog.h"


static Display lcd;
static Rotary rotary;
static struct menu_entry actions[] = {
    {"Examine", NULL},
    {"Foo", NULL},
    {"Bar", NULL},
    {"Baz", NULL},
    {"qux", NULL},
    {"quux", NULL},
};


static Menu menu("Main menu:", actions, ENTRYCOUNT(actions));


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
    // analogReference(INTERNAL);
    analogReference(EXTERNAL);
}

// #define RES (((float)30) / ((float)1024))
#define RES 0.3

void 
loop() {
    struct menu_entry *prog;
    /* Greeting */
    Dialog::show(PROJECT, VVERSION);
    
    int val1;
    double v;
    while (true) {
        val1 = analogRead(A0);
        v = ((double)val1) * ((double)0.016);
        Serial.println(v);
        lcd.clear();
        lcd.print(val1);
        lcd.setCursor(0, 1);
        lcd.printDouble(v, 10000);
        lcd.write('V');
        delay(500);
    }

    while (true) {
        /* Main menu */
        prog = menu.show();
        
        /* Selected */
        Dialog::show("Selected: ", prog->caption);
    }
    while (true);
}
