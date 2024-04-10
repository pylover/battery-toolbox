#include "common.h"


void
Splash::wait() {
    this->waiting = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(PROJECT);
    lcd.setCursor(0, 1);
    lcd.print(VVERSION);
    rotary.consumer = this;
    while (this->waiting);
    lcd.clear();
    lcd.setCursor(0, 0);
    rotary.consumer = NULL;
}


int 
Splash::rotated(int amount) {
    this->waiting = false;
}


void
Splash::pushed() {
    this->waiting = false;
}


void
Splash::show() {
    Splash *splash = new Splash();
    splash->wait();
    delete splash;
}
