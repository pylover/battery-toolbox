#ifndef LCD_H
#define LCD_H


#include <LiquidCrystal.h>


#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 10
#define LCD_D5 9
#define LCD_D6 8
#define LCD_D7 7


class Display: public LiquidCrystal {
public:
    Display(): LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) {};
    void begin();
    printl(char *data);
};


#endif  // LCD_H
