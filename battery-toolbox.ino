#include <avr/interrupt.h>

#include "common.h"
#include "menu.h"
#include "display.h"
#include "rotary.h"


#define S_SPLASH 1
#define S_MENU (1 << 1)


static Display lcd;
static Rotary joy;
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

void 
joy_rotated() {
    if (status & S_SPLASH) {
        return;
    }

    joy.tick();
    int pos = joy.getPosition();
    if (!pos) {
        return;
    }

    joy.setPosition(0);
    menu.scroll(pos);
    
    // static int pos = 0;
    // joy.tick();
    // int newPos = joy.getPosition();
    // if (pos == newPos) {
    //     return;
    // }

    // pos = newPos;
    // info("pos: ");
    // infoln(newPos);
    // joy.setPosition(0);
    // pos = 0;
}


void
joy_pushed() {
    if (status & S_SPLASH) {
        status = S_MENU;
        return;
    }
    infoln("Rotary Push");
}


ISR(PCINT1_vect) {
    if (PINC & (1 << PINC4)) {
        joy_pushed();
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

    lcd.begin();
    joy.begin();
}


void 
loop() {
    /* Greeting */
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(PROJECT);
    lcd.setCursor(0, 1);
    lcd.print(VVERSION);

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
