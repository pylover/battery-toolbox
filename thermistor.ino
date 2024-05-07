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

#include "lcd2x16.h"
#include "thermistor.h"


Thermistor::Thermistor(int pin, struct thermistor th, float r) {
    this->pin = pin;
    this->thermistor = th;
    this->resistor = r;
    pinMode(pin, INPUT);
}


float
Thermistor::get_temp() {
    /* Steinhart-Hart
     * https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
     */
    int i;
    float v = 0;

    for (i = 0; i < THERMISTOR_SAMPLES; i++) {
        v += (float)analogRead(this->pin);
    }
    v /= THERMISTOR_SAMPLES;
    float resistance = this->resistor * (1023.0 / v - 1.0);
    float logn = log(resistance);
    float logn3 = logn * logn * logn;
    struct thermistor *th = &this->thermistor;
    float t = 1.0 / (th->a + th->b * logn + th->c * logn3);

    /* Convert Kelvin to Celcius */
    t -= 273.15;
    return t;
}


void
Thermistor::print(int precision, int len) {
    lcd.printu(this->get_temp(), CHAR_DEGREE, precision, len);
}
