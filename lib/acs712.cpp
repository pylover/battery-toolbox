#include <Arduino.h>

#include "acs712.h"


ACS712::ACS712(int pin, float coefficient) {
    this->pin = pin;
    this->coefficient = coefficient;
}


float 
ACS712::get_ampere() {
    int i;
    float v = 0;

    for (i = 0; i < ACS712_SAMPLES; i++) {
        v += (float)analogRead(this->pin);
    }
    v /= ACS712_SAMPLES;

    v *= this->coefficient;
    v -= 2.3718627;
    return v * 10;
}


int
ACS712::print(Print *display, int precision, int length) {
    float v = this->get_ampere();
    float vabs = abs(v);
    int p = 0;
    char *u = "A";

    if (vabs) {
        if (vabs < 1) {
            u = "mA";
            v *= 1000;
        }
        else {
            p = precision;
        }
    }
    return Printer::print_unit(display, v, p, u, length);
}

