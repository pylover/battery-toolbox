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
#include "discharge.h"


int
Discharge::main() {
    this->duty = 0;
   
    float v = NumInput::show("Cut-off voltage:", 'V', 0, 14, db.discharge.v, 
            0.1, 1);
    float i = NumInput::show("Current:", 'A', 0, 14, db.discharge.i, 0.05, 2);

    if (v != db.discharge.v) {
        db.discharge.v = v;
        db.dirty = true;
    }

    if (i != db.discharge.i) {
        db.discharge.i = i;
        db.dirty = true;
    }

    if (db.dirty) {
        db_commit(&db);
    }

    lcd.clear();
    lcd.print("Discharging ");
    char c = 0;
    while (this->active) {
        lcd.setCursor(15, 0);
        lcd.write(c++ + CHAR_FULL);
        c %= 4;

        lcd.setCursor(0, 1);
        // lcd.fill(' ', dutyloc + lcd.print(this->duty));
        vmeter.printlow(1, 5);
        lcd.write(' ');
        ammeter.print(1, 5);
        lcd.write(' ');
        heatsink.print(0, 4);
        pwm_set(DISCHARGE_PWMPIN, this->duty);
        delay(300);
    }

    digitalWrite(DISCHARGE_PWMPIN, 0);
    return 0;
}
    

int 
Discharge::rotated(int pos) {
    if (pos < 0) {
        this->duty = 0;
    }
    else if (pos > 255) {
        this->duty = 255;
    }
    else {
        this->duty = pos;
    }
    return this->duty;
}
