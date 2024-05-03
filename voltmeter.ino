#include <Arduino.h>

#include "voltmeter.h"


VoltMeter::VoltMeter(int pin, float r1, float r2) {
    this->pin = pin;
    this->coefficient = VREF * (r1 + r2) / r2 / 1024.0;
    pinMode(pin, INPUT);
}


float 
VoltMeter::get_voltage() {
    int i;
    float v = 0;

    for (i = 0; i < VOLTMETER_SAMPLES; i++) {
        v += analogRead(this->pin);
    }
    v /= (float)VOLTMETER_SAMPLES;
    return v * this->coefficient;
}


void
VoltMeter::print(Print *display, int precision, int length) {
    float v = this->get_voltage();
    printu(display, v, 'V', precision, length);
}
