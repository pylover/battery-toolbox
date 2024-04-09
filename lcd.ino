#include "lcd.h"


LCD::begin(uint8_t cols, uint8_t lines, uint8_t charsize) {
    LiquidCrystal::begin(cols, lines, charsize);
    lcd.noAutoscroll();
    lcd.createChar(0, char_down);
    lcd.createChar(1, char_updown);
}
