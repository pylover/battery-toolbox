/*
Copyright (c) 2024, Vahid Mardani <vahid.mardani@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation  and/or other materials provided with the distribution.
3. Neither the names of the copyright holders nor the names of any
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
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


static byte char_miliampere[8] = {
    0b00100,
    0b01010,
    0b11111,
    0b10001,
    0b00000,
    0b11011,
    0b10101,
    0b10101,
};


static byte char_microampere[8] = {
    0b00100,
    0b01010,
    0b11111,
    0b10001,
    0b00000,
    0b01001,
    0b01111,
    0b10000,
};


static byte char_milivolt[8] = {
    0b10001,
    0b10001,
    0b01010,
    0b00100,
    0b00000,
    0b11011,
    0b10101,
    0b10101,
};


static byte char_microvolt[8] = {
    0b10001,
    0b10001,
    0b01010,
    0b00100,
    0b00000,
    0b01001,
    0b01111,
    0b10000,
};


LCD2X16::LCD2X16(int rs, int en, int d4, int d5, int d6, int d7):
        LiquidCrystal(rs, en, d4, d5, d6, d7) {
    LiquidCrystal::begin(16, 2, LCD_5x8DOTS);
    this->noAutoscroll();
    this->createChar(CHAR_DOWN, char_down);
    this->createChar(CHAR_UPDOWN, char_updown);
    this->createChar(CHAR_MILIAMPERE, char_miliampere);
    this->createChar(CHAR_MICROAMPERE, char_microampere);
    this->createChar(CHAR_MILIVOLT, char_milivolt);
    this->createChar(CHAR_MICROVOLT, char_microvolt);
}


int
LCD2X16::fill(char c, int from = 0, int to = 15) {
    for (; from <= to; from++) {
        this->write(c);
    }

    return to - from;
}


void
LCD2X16::printu(float val, const char unit, int precision, int len,
        bool prefix = true) {
    unsigned p = pow(10, precision) + 1;
    char r = 0;
    char *v;
    char buffer[len];
    float absval = abs(val);

    /* Reduce len to freeup space for unit */
    if (unit) {
        len--;
    }

    /* round */
    absval /= p;
    absval *= p;

    /* unit and ratio */
    if (absval == 0) {
        r = 0;
        precision = 0;
        val = 0;
    }
    else if (prefix && (absval < 1)) {
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

    val /= p;
    val *= p;
    v = dtostrf(val, len, precision, buffer);
    this->print(v);
    if (r) {
        this->write(r);
    }
    if (unit) {
        this->write(unit);
    }
}
