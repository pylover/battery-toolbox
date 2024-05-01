#include <Arduino.h>

#include "voltmeter.h"


VoltMeter::VoltMeter(int pin, float coefficient) {
    this->pin = pin;
    this->coefficient = coefficient;
}


float 
VoltMeter::get_voltage() {
    int i;
    float v = 0;

    for (i = 0; i < VOLTMETER_SAMPLES; i++) {
        v += (float)analogRead(this->pin);
    }
    v /= VOLTMETER_SAMPLES;

    return v * this->coefficient;
}


void
VoltMeter::print(Print *display, int precision, int length) {
    float v = this->get_voltage();
    printu(display, v, 'V', precision, length);
}
