#include "examine.h"


int
Examine::main() {
    lcd.write("Examination");

    while (this->active) {
        lcd.setCursor(0, 1);
        vmeter.printhigh(1, 5);
        lcd.write(' ');
        ammeter.print(2, 6);
        lcd.write(' ');
        heatsink.print(0, 3);
        delay(500);
    }
    return 0;
}
