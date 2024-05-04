#include "lcd2x16.h"


static byte char_down[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b10001,
    0b01010,
    0b00100,
};


static byte char_updown[8] = {
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000,
    0b10001,
    0b01010,
    0b00100,
};


static byte char_degree[8] = {
    0b01000,
    0b10100,
    0b01000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
};


static byte char_backslash[8] = {
    0b00000,
    0b10000,
    0b01000,
    0b00100,
    0b00010,
    0b00001,
    0b00000,
    0b00000,
};


static byte char_full[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
};


static byte char_75p[8] = {
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
};


static byte char_50p[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
};


static byte char_25p[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
};


void
LCD2X16::begin() {
    LiquidCrystal::begin(16, 2, LCD_5x8DOTS);
    this->noAutoscroll();
    this->createChar(CHAR_DOWN, char_down);
    this->createChar(CHAR_UPDOWN, char_updown);
    this->createChar(CHAR_DEGREE, char_degree);
    this->createChar(CHAR_BACKSLASH, char_backslash);
    this->createChar(CHAR_FULL, char_full);
    this->createChar(CHAR_75P, char_75p);
    this->createChar(CHAR_50P, char_50p);
    this->createChar(CHAR_25P, char_25p);
}


int
LCD2X16::fill(char c, int from=0, int to=15) {
    for (; from <= to; from++) {
        this->write(c);
    }

    return to - from;
}
    

void
LCD2X16::printu(float val, const char unit, int precision, int len) {
    unsigned p = pow(10, precision) + 1;
    char r = 0;
    char buffer[len];
    float absval = abs(val);

    /* Reduce len to freeup space for unit */
    len--;

    /* round */
    absval /= p;
    absval *= p;
    // val /= p;
    // val *= p;

    /* unit and ratio */
    if (absval == 0) {
        r = 0;
        precision = 0;
        val = 0;
    }
    else if (absval < 1) {
        if (absval < .000001) {
            val *= 1000000000;
            r = 'n';
        }
        else if (absval < .001) {
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

    String v = dtostrf(val, len, precision, buffer);
    this->print(v);
    if (r) {
        this->write(r);
    }
    this->write(unit);
}
