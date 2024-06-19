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
#include "program.h"


void
Program::ask() {
    bool dirty = false;
    struct watt *entry = this->dbentry_get();

    this->voltage_threshold = NumInput::show("Cut-off voltage:", 0, 14,
            entry->voltage, VOLTAGE_STEP, 1, 'V', CHAR_MILIVOLT);

    this->current_threshold = NumInput::show("Current:", 0,
            MAXPOWER / this->voltage_threshold, entry->current, CURRENT_STEP,
            2, 'A', CHAR_MILIAMPERE);

    if (this->voltage_threshold != entry->voltage) {
        entry->voltage = this->voltage_threshold;
        dirty = true;
    }

    if (this->current_threshold != entry->current) {
        entry->current = this->current_threshold;
        dirty = true;
    }

    if (dirty) {
        db_commit();
    }
}


void
Program::tick(unsigned long ticks, float t, float c, float sv, float lv) {
    /* Nothing to do when program was completed */
    if (this->status == CS_DONE) {
        return;
    }

    /* Check for completion */
    if ((ticks > 5) && this->completed(sv, lv)) {
        this->updateduty(0);
        this->status = CS_DONE;
        play(BUZZER, programfinish_melody, &this->active);
        return;
    }

    /* Monitoring and fast reactions */
    if (this->duty && ((t > MAXTEMP) || (c > this->current_threshold))) {
        this->status = CS_COOLING;
        this->risk = this->duty - 1;
        this->updateduty(max(0, this->duty - COOLING_STEPDOWN));
        BUZZ(100);
        return;
    }

    /* Increase risk threshold if possible */
    if ((ticks % 100 == 0) && (this->risk < 255) &&
            ((this->current_threshold - c) > (CURRENT_STEP * 3))) {
        this->risk++;
        this->status = CS_PASSING;
        BUZZ(20);
        delay(20);
        BUZZ(20);
    }

    /* Do something */
    if ((this->status != CS_COOLING) || (ticks % 10 == 0)) {
        this->status = CS_PASSING;
        this->updateduty(min(this->risk, this->duty + 1));
    }
}


void
Program::prepare() {
    this->risk = 255;
    this->updateduty(0);
    this->ask();
    rotary.setPosition(this->current_threshold / CURRENT_STEP);
    lcd.clear();
}


void
Program::terminate() {
    this->updateduty(0);
}


int
Program::main() {
    unsigned long ticks = 0;
    unsigned long start;
    unsigned long milis;
    float t, c, sv, lv;

    this->prepare();

    /* main loop */
    start = millis();
    while (this->active) {
        t = heatsink.get_temp();
        c = ammeter.get_ampere();
        sv = this->sourcevoltage_get();
        lv = this->loadvoltage_get();

        this->tick(ticks++, t, c, sv, lv);
        milis =  millis() - start;

        if (milis > 600) {
            this->printstatus(t, c, sv, lv);
            start = millis();
        }
        delay(10);
    }

    this->terminate();
    return 0;
}


int
Program::rotated(int pos) {
    float c = pos * CURRENT_STEP;

    if (c < 0) {
        this->current_threshold = 0;
    }
    else if (c > MAX_CURRENT) {
        this->current_threshold = MAX_CURRENT;
    }
    else {
        this->current_threshold = CURRENT_STEP * pos;
    }
    return this->current_threshold / CURRENT_STEP;
}


void
Program::mosfet(int d) {
    analogWrite(MOSFET1, d);
    analogWrite(MOSFET2, d);
}


void
Program::updateduty(int d) {
    int nd;
    if (d >= 255) {
        nd = 255;
    }
    else if (d < 0) {
        nd = 0;
    }
    else {
        nd = d;
    }

    if (this->duty != nd) {
        this->duty = nd;
        this->mosfet(nd);
    }
}


float
Program::sourcevoltage_get() {
    return vmeter.vhigh();
}


float
Program::loadvoltage_get() {
    return vmeter.vdiff();
}


void
Program::printstatus(float t, float c, float sv, float lv) {
    float d = (float)this->duty * 100.0 / 255;
    char *title = this->title_get();
    float cth = this->current_threshold;

    lcd.clear();
    if (this->status == CS_DONE) {
        lcd.print(title);
        lcd.print(" Completed");
    }
    else {
        /* Caption */
        lcd.write(title[0]);

        /* Duty cycle */
        lcd.printuu(d, 1, 5, '%');

        /* Current */
        lcd.setCursor(7, 0);
        lcd.printuu(c, 2, 4, 'A', CHAR_MILIAMPERE, CHAR_MICROAMPERE);
        lcd.write('<');
        lcd.printuu(cth, 2, 4, 'A', CHAR_MILIAMPERE, CHAR_MICROAMPERE);
    }

    /* Voltage */
    lcd.setCursor(0, 1);
    lcd.write('S');
    lcd.printuu(sv, 1, 4, 'V', CHAR_MILIVOLT, CHAR_MICROVOLT);
    lcd.print(" L");
    lcd.printuu(lv, 1, 4, 'V', CHAR_MILIVOLT, CHAR_MICROVOLT);
    lcd.write(' ');
    lcd.printuu(t, 0, 4, CHAR_DEGREE);
}
