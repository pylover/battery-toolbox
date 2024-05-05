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
#include "charge.h"


void
Charge::ask() {
    this->maxv = NumInput::show("Cut-off voltage:", 'V', 0, 14, 
            db.charge.voltage, 0.1, 1);

    this->maxc = NumInput::show("Current:", 'A', 0, 10, 
            db.charge.current, 0.05, 2);
    
    if (this->maxv != db.charge.voltage) {
        db.charge.voltage = this->maxv;
        db.dirty = true;
    }

    if (this->maxc != db.charge.current) {
        db.charge.current = this->maxc;
        db.dirty = true;
    }

    if (db.dirty) {
        db_commit(&db);
    }
}


#define COOLING_STEPDOWN 10


void
Charge::tick(unsigned int ticks, float t, float v, float c) {
    /* Check for completion */
    if (this->status == CS_DONE) {
        return;
    }

    if (v >= this->maxv) {
        this->mosfet(0);
        this->status = CS_DONE;
        return;
    }

    /* Monitoring and fast reactions */
    if ((t > MAXTEMP) || (c > this->maxc)) {
        Serial.print("Overheat, duty: ");
        Serial.println(this->duty);
        this->status = CS_COOLING;
        this->risk = this->duty - 1;
        this->mosfet(max(0, this->duty - COOLING_STEPDOWN));
        BUZZ(100);
        return;
    }

    if (ticks % 100 == 0) {
        if ((this->maxc - c) > .1) {
            this->risk++;
        }
    }
    /* Do something */
    if ((this->status != CS_COOLING) || (ticks % 10 == 0)) {
        this->status = CS_CHARGING;
        this->mosfet(min(this->risk, this->duty + 1));
        // Serial.print(ticks);
        // Serial.print(" Charging, duty: ");
        // Serial.println(this->duty);
    }
}


int
Charge::main() {
    this->risk = 255;
    this->mosfet(0);
    
    this->ask(); 

    lcd.clear();
    int frame = 3;
    unsigned int ticks = 0;
    float t, v, c;
    while (this->active) {
        t = heatsink.get_temp();
        v = vmeter.vdiff();
        c = ammeter.get_ampere();

        if (!(ticks % 30)) {
            this->printstatus(frame--, t, v, c);
            frame = (frame + 4) % 4;
        }
        
        this->tick(ticks++, t, v, c);
        delay(10);
    }

    this->mosfet(0);
    return 0;
}
    

int 
Charge::rotated(int pos) {
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



int 
Charge::mosfet(int d) {
    if (d > 255) {
        this->duty = 255;
    }
    else if (d < 0) {
        this->duty = 0;
    }
    else {
        this->duty = d;
    }
    pwm_set(MOSFET, this->duty);
}


void 
Charge::printstatus(int counter, float t, float v, float c) {
    float d = (float)this->duty * 100.0 / 255;

    lcd.setCursor(0, 0);
    if (this->status == CS_DONE) {
        lcd.print("Charge Completed");

        /* Voltage */
        lcd.setCursor(0, 1);
        lcd.printu(v, 'V', 3, 9);
    
        /* Temperature */
        lcd.setCursor(10, 1);
        lcd.printu(t, CHAR_DEGREE, 1, 6);
        return;
    }
    
    /* Animation */
    lcd.write(counter-- + CHAR_FULL);
    lcd.write("C");

    /* Duty Cycle */
    lcd.setCursor(3, 0);
    lcd.printu(d, '%', 1, 6, false);
    
    /* Temperature */
    lcd.setCursor(10, 0);
    lcd.printu(t, CHAR_DEGREE, 1, 6);

    /* Voltage */
    lcd.setCursor(0, 1);
    lcd.printu(v, 'V', 2, 5);

    /* Current */
    lcd.printu(c, 0, 1, 5);
    lcd.write('/');
    lcd.printu(this->maxc, 'A', 2, 5);
}
