#include "examine.h"


int
Examine::main() {
    lcd.write("Examination");

    while (this->active) {
        lcd.setCursor(0, 1);
        voltmeter.print(&lcd, 1, 5);
        lcd.write(' ');
        ammeter.print(&lcd, 2, 6);
        lcd.write(' ');
        heatsink.print(&lcd, 0, 3);
        delay(500);
    }
    return 0;
}
