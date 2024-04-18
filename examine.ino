#include "examine.h"


int
Examine::execute() {
    lcd.clear();
    lcd.print("Hey");
    this->waiting = true;
    while (this->waiting);
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
