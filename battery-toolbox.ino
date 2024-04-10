#include <avr/interrupt.h>

#include "common.h"
#include "menu.h"
#include "display.h"
#include "rotary.h"
#include "splash.h"


#define S_SPLASH 1
#define S_MENU (1 << 1)


static Display lcd;
static Rotary rotary;
static volatile int status = S_SPLASH;
static struct menu_entry actions[] = {
    {"1. 12345678901", NULL},
    {"2. Foo", NULL},
    {"3. Bar", NULL},
    {"4. Baz", NULL},
    {"5. qux", NULL},
    {"6. quux", NULL},
};


static Menu menu("Select one:", actions, 6);


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
    /* Greeting */
    Splash *splash = new Splash();
    splash->wait();
    delete splash;

    while (status & S_SPLASH);
    menu.main();

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("What to do?");
    // lcd.setCursor(0, 1);
    // lcd.print("^");
    // lcd.write(CHAR_DOWN);
    // lcd.write(CHAR_UPDOWN);
    while (true);
}
