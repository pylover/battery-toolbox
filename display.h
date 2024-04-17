#ifndef LCD_H
#define LCD_H


#include <LiquidCrystal.h>


#define LCD_RS 13
#define LCD_EN 12
#define LCD_D4 8
#define LCD_D5 7
#define LCD_D6 5
#define LCD_D7 4


byte char_down[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
};


byte char_updown[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
};


byte char_degree[8] = {
  0b00010,
  0b00101,
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};


#define CHAR_UP '^'
#define CHAR_DOWN byte(0)
#define CHAR_UPDOWN byte(1)
#define CHAR_DEGREE byte(2)


class Display: public LiquidCrystal {
public:
    Display(): LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) {
    };
    void begin();
    int fill(char c, int from=0, int to=15);
};


#endif  // LCD_H
