#ifndef LCD2X16_H
#define LCD2X16_H


#include <Arduino.h>

#include <LiquidCrystal.h>


#define CHAR_UP '^'
#define CHAR_DOWN byte(0)
#define CHAR_UPDOWN byte(1)
#define CHAR_DEGREE byte(2)
#define CHAR_BACKSLASH byte(3)
#define CHAR_FULL byte(4)
#define CHAR_75P byte(5)
#define CHAR_50P byte(6)
#define CHAR_25P byte(7)


class LCD2X16: public LiquidCrystal {
public:
    LCD2X16(int rs, int en, int d4, int d5, int d6, int d7):
        LiquidCrystal(rs, en, d4, d5, d6, d7) {
    };
    void begin();
    int fill(char c, int from=0, int to=15);
    void printu(float val, char unit, int precision, int len);
};


#endif  // LCD2X16_H
