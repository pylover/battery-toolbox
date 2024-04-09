#include <LiquidCrystal.h>


#define PROJECT "Battery Toolbox"
#define VERSION "0.1.0a"
#define VVERSION "v"VERSION"(pylover)"


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
}


void 
loop() {
    /* Greeting */
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(PROJECT);
    lcd.setCursor(0, 1);
    lcd.print(VVERSION);

    while (true);
    delay(1000);
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("What to do?");
}
