#include "dialog.h"


Dialog::Dialog(String first, String second) {
    lcd.clear();
    lcd.print(first);
    lcd.setCursor(0, 1);
    lcd.print(second);
}


void
Dialog::wait() {
    this->waiting = true;
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


static void
Dialog::show(String first, String second) {
    Dialog *d = new Dialog(first, second);
    d->wait();
    delete d;
}
