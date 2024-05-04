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
    template<typename T>
    void
    printu(T val, char unit, int precision, int len) {
        unsigned p = pow(10, precision) + 1;
        char r = 0;

        /* Reduce len to freeup space for unit */
        len--;

        /* round */
        val /= p;
        val *= p;

        /* unit and ratio */
        if (val == 0) {
            r = 0;
            precision = 0;
        }
        else if (val < 1) {
            if (val < .000001) {
                val *= 1000000000;
                r = 'n';
            }
            else if (val < .001) {
                val *= 1000000;
                r = 'u';
            }
            else {
                val *= 1000;
                r = 'm';
            }
            len--;
            precision = 0;
        }

        char buffer[len];
        String v = dtostrf(val, len, precision, buffer);
        this->print(v);
        if (r) {
            this->write(r);
        }
        this->write(unit);
    }
};


#endif  // LCD2X16_H
