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
#ifndef LCD2X16_H_
#define LCD2X16_H_


#include <Arduino.h>

#include <LiquidCrystal.h>


#define CHAR_UP byte(94)
#define CHAR_DEGREE byte(223)
#define CHAR_DOWN byte(0)
#define CHAR_UPDOWN byte(1)
#define CHAR_MILIAMPERE byte(2)
#define CHAR_MICROAMPERE byte(3)
#define CHAR_MILIVOLT byte(4)
#define CHAR_MICROVOLT byte(5)


class LCD2X16: public LiquidCrystal {
 public:
    LCD2X16(int rs, int en, int d4, int d5, int d6, int d7);
    void begin();
    int fill(char c, int from = 0, int to = 15);
    void printuu(float val, int precision, int len, const char unit = 0,
        const char miliunit = 0, const char microunit = 0);
};


#endif  // LCD2X16_H_
