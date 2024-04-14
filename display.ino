#include "display.h"


void
Display::begin() {
    LiquidCrystal::begin(16, 2, LCD_5x8DOTS);
    this->noAutoscroll();
    this->createChar(0, char_down);
    this->createChar(1, char_updown);
}


int
Display::fill(char c, int from=0, int to=15) {
    for (; from < to; from++) {
        this->write(c);
    }

    return to - from;
}
