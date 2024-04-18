#include "dialog.h"


int
Window::showwait() {
    rotary.consumer = this;
    int status =this->execute();
    rotary.consumer = NULL;
    return status;
}


Dialog::Dialog(char *first, char *second) {
    this->first = first;
    this->second = second;
}


int
Dialog::execute() {
    lcd.clear();
    lcd.print(this->first);
    if (second) {
        lcd.setCursor(0, 1);
        lcd.print(this->second);
    }
    this->waiting = true;
    while (this->waiting);
    return 0;
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


static int
Dialog::show(char * first, char * second) {
    Dialog *d = new Dialog(first, second);
    int status = d->showwait();
    delete d;
    return status;
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
    d->showwait();
    int value = d->value;
    delete d;
    return value;
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
