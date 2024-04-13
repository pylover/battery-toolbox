#ifndef LCD_H
#define LCD_H


#include <LiquidCrystal.h>


#define LCD_RS 13
#define LCD_EN 12
#define LCD_D4 8
#define LCD_D5 7
#define LCD_D6 5
#define LCD_D7 4


class Display: public LiquidCrystal {
public:
    Display(): LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) {
    };
    void begin();
    int fill(char c, int from=0, int to=15);
    int printDouble(double val, unsigned int precision);
};


#endif  // LCD_H
