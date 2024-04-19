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


int
VoltMeter::print(Print *display, int precision, int length) {
    float v = this->get_voltage();
    int p = 0;
    char *u = "V";

    if (v) {
        if (v < 1) {
            u = "mV";
            v *= 1000;
        }
        else {
            p = precision;
        }
    }
    return Printer::print_unit(display, v, p, u, length);
}
