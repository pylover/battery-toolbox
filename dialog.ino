#include "dialog.h"


Dialog::Dialog(char *first, char *second) {
    lcd.clear();
    lcd.print(first);
    if (second) {
        lcd.setCursor(0, 1);
        lcd.print(second);
    }
}


void
Dialog::wait() {
    this->waiting = true;
    rotary.consumer = this;
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
Dialog::show(char * first, char * second) {
    Dialog *d = new Dialog(first, second);
    d->wait();
    delete d;
}



IntegerInputDialog::IntegerInputDialog(char * title, int minval, int maxval, 
            int initial): Dialog(title, NULL) {
    this->minval = minval;
    this->maxval = maxval;
    this->value = initial;
    rotary.setPosition(initial);
    this->update();
}


void
IntegerInputDialog::update() {
    lcd.setCursor(0, 1);
    int i = lcd.print(this->value);
    lcd.fill(' ', i);
}


static int 
IntegerInputDialog::show(char * title, int minval, int maxval, int initial) {
    IntegerInputDialog *d = new IntegerInputDialog(title, minval, maxval, 
            initial);
    d->wait();
    delete d;
    return d->value;
}


int 
IntegerInputDialog::rotated(int pos) {
    if (pos == this->value) {
        return pos;
    }
    else if (pos < this->minval) {
        pos = this->minval;
    }
    else if (pos > this->maxval) {
        pos = this->maxval;
    }

    this->value = pos;
    this->update();
    this->waiting = false;
    return pos;
}
