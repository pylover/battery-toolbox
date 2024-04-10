#include "display.h"


void
Display::begin() {
    LiquidCrystal::begin(16, 2, LCD_5x8DOTS);
    lcd.noAutoscroll();
    lcd.createChar(0, char_down);
    lcd.createChar(1, char_updown);
}


int
Display::printl(char *data) {
    int i = LiquidCrystal::print(data);
    for (; i < 15; i++) {
        lcd.write(' ');
    }

    return i;
}
