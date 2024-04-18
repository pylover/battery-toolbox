#include "examine.h"


int
Examine::execute() {
    int i;
    this->waiting = true;
    while (this->waiting) {
        lcd.clear();
        voltmeter.print(&lcd, 2);
        lcd.write(' ');
        ammeter.print(&lcd, 2);
        lcd.setCursor(0, 1);
        heatsink.print(&lcd, 2);
        delay(500);
    }
    return 0;
}
    

int 
Examine::rotated(int pos) {
    this->waiting = false;
    return pos;
}


void 
Examine::pushed() {
    this->waiting = false;
}
