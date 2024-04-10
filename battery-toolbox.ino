#include <avr/interrupt.h>

#include "common.h"
#include "menu.h"
#include "display.h"
#include "rotary.h"
#include "splash.h"


static Display lcd;
static Rotary rotary;
static struct menu_entry actions[] = {
    {"1. DISCHARGE", NULL},
    {"2. Foo", NULL},
    {"3. Bar", NULL},
    {"4. Baz", NULL},
    {"5. qux", NULL},
    {"6. quux", NULL},
};


static Menu menu("Select one:", actions, ENTRYCOUNT(actions));


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
}


void 
loop() {
    struct menu_entry *prog;
    /* Greeting */
    Splash::show();

    while (true) {
        /* Main menu */
        prog = menu.show();
        
        /* Selected */
        info("Selected: ");
        infoln(prog->caption);
    }
    while (true);
}
