#include "display.h"


Display::begin() {
    LiquidCrystal::begin(16, 2, LCD_5x8DOTS);
    lcd.noAutoscroll();
    lcd.createChar(0, char_down);
    lcd.createChar(1, char_updown);
}
