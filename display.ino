#include "display.h"


void
Display::begin() {
    LiquidCrystal::begin(16, 2, LCD_5x8DOTS);
    this->noAutoscroll();
    this->createChar(CHAR_DOWN, char_down);
    this->createChar(CHAR_UPDOWN, char_updown);
    this->createChar(CHAR_DEGREE, char_degree);
}


int
Display::fill(char c, int from=0, int to=15) {
    for (; from < to; from++) {
        this->write(c);
    }

    return to - from;
}
