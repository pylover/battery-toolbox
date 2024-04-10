#include "common.h"


void
Dialog::wait() {
    this->waiting = true;
    lcd.clear();
    this->render();
    rotary.consumer = this;
    rotary.setPosition(0);
    while (this->waiting);
    lcd.clear();
    rotary.consumer = NULL;
}


int 
Dialog::rotated(int pos) {
    this->waiting = false;
    return pos;
}


void
Dialog::pushed() {
    this->waiting = false;
}


void
Splash::show() {
    Splash *d = new Splash();
    d->wait();
    delete d;
}


void
Splash::render() {
    lcd.print(PROJECT);
    lcd.setCursor(0, 1);
    lcd.print(VVERSION);
}
