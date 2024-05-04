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
VoltMeter::vhigh() {
    int i;
    float v = 0;

    for (i = 0; i < VOLTMETER_SAMPLES; i++) {
        v += analogRead(this->pinh);
    }
    v /= (float)VOLTMETER_SAMPLES;
    return v * this->coefficient;
}


void
VoltMeter::print(Print *display, int precision, int length) {
    float v = this->vhigh();
    printu(display, v, 'V', precision, length);
}
