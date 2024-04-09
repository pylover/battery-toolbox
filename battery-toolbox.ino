#include <LiquidCrystal.h>


#define __VER__ "0.1.0a"


/* lcd pinout */
#define RS 12 
#define EN 11 
#define D4 5 
#define D5 4 
#define D6 3 
#define D7 2
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


void 
setup() {
    /* Display settings */
    lcd.begin(16, 2);
    lcd.noAutoscroll();
    lcd.clear();
}


void 
loop() {
    lcd.setCursor(0, 0);
    lcd.print("Battery Toolbox");
    lcd.setCursor(0, 1);
    lcd.print("Ver " __VER__);
}
