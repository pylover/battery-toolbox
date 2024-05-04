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
#include <Arduino.h>

#include "voltmeter.h"


VoltMeter::VoltMeter(int pinh, int pinl, float r1, float r2) {
    this->pinl = pinl;
    this->pinh = pinh;
    this->coefficient = VREF * (r1 + r2) / r2 / 1024.0;
    pinMode(pinh, INPUT);
    pinMode(pinl, INPUT);
}


float 
VoltMeter::read(int pin) {
    int i;
    float v = 0;

    for (i = 0; i < VOLTMETER_SAMPLES; i++) {
        v += analogRead(pin);
    }
    v /= (float)VOLTMETER_SAMPLES;
    return v * this->coefficient;
}


float 
VoltMeter::vhigh() {
    return this->read(this->pinh);
}


float 
VoltMeter::vlow() {
    return this->read(this->pinl);
}


float 
VoltMeter::vdiff() {
    return this->read(this->pinh) - this->read(this->pinl);
}


void
VoltMeter::printhigh(int precision, int len) {
    lcd.printu(this->vhigh(), 'V', precision, len);
}
    

void
VoltMeter::printlow(int precision, int len) {
    lcd.printu(this->vlow(), 'V', precision, len);
}


void
VoltMeter::printdiff(int precision, int len) {
    lcd.printu(this->vhigh() - this->vlow(), 'V', precision, len);
}
