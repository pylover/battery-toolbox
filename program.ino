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

    this->voltage_threshold = NumInput::show("Cut-off voltage:", 'V', 0, 14,
            entry->voltage, VOLTAGE_STEP, 1);

    this->current_threshold = NumInput::show("Current:", 'A', 0, 10,
            entry->current, CURRENT_STEP, 2);

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
Program::tick(unsigned int ticks, float t, float v, float c) {
    /* Nothing to do when program was completed */
    if (this->status == CS_DONE) {
        return;
    }

    /* Check for completion */
    if (this->completed(v)) {
        this->mosfet(0);
        this->status = CS_DONE;
        play(BUZZER, programfinish_melody, &this->active);
        return;
    }

    /* Monitoring and fast reactions */
    if (this->duty && ((t > MAXTEMP) || (c > this->current_threshold))) {
        this->status = CS_COOLING;
        this->risk = this->duty - 1;
        this->mosfet(max(0, this->duty - COOLING_STEPDOWN));
        Serial.print("Overheat, decreasing the risk factor. duty: ");
        Serial.println(this->duty);
        BUZZ(100);
        return;
    }

    /* Increase risk threshold if possible */
    if ((ticks % 100 == 0) && (this->risk < 255) &&
            ((this->current_threshold - c) > (CURRENT_STEP * 3))) {
        Serial.print("Increase the risk factor: ");
        Serial.println(++this->risk);
        BUZZ(20);
        delay(20);
        BUZZ(20);
    }

    /* Do something */
    if ((this->status != CS_COOLING) || (ticks % 10 == 0)) {
        this->status = CS_PASSING;
        this->mosfet(min(this->risk, this->duty + 1));
    }
}


void
Program::prepare() {
    this->risk = 255;
    this->mosfet(0);
    this->ask();
    rotary.setPosition(this->current_threshold / CURRENT_STEP);
    lcd.clear();
}


void
Program::terminate() {
    this->mosfet(0);
}


int
Program::main() {
    int frame = 3;
    unsigned int ticks = 0;
    float t, v, c;

    this->prepare();

    /* main loop */
    while (this->active) {
        t = heatsink.get_temp();
        c = ammeter.get_ampere();
        pwm_set(MOSFET, 0);
        v = this->voltage_get();
        pwm_set(MOSFET, this->duty);

        if (!(ticks % 30)) {
            this->printstatus(frame--, t, v, c);
            frame = (frame + 4) % 4;
        }

        this->tick(ticks++, t, v, c);
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


int
Program::mosfet(int d) {
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
Program::printstatus(int frame, float t, float v, float c) {
    float d = (float)this->duty * 100.0 / 255;

    lcd.setCursor(0, 0);
    if (this->status == CS_DONE) {
        lcd.print(this->title_get());
        lcd.print(" Completed");

        /* Voltage */
        lcd.setCursor(0, 1);
        lcd.printu(v, 'V', 3, 9);

        /* Temperature */
        lcd.setCursor(10, 1);
        lcd.printu(t, CHAR_DEGREE, 1, 6);
        return;
    }

    /* Animation */
    this->animate(frame);

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
    lcd.printu(c, 0, 2, 5);
    lcd.write('/');
    lcd.printu(this->current_threshold, 'A', 2, 5);
}
