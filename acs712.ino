#include <Arduino.h>

#include "acs712.h"


ACS712::ACS712(int pin, float coefficient) {
    this->pin = pin;
    this->coefficient = coefficient;
    pinMode(pin, INPUT);
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
    v -= 23.718750;
    return v;
}


void
ACS712::print(int precision, int len) {
    float v = this->get_ampere();
    lcd.printu(v, 'A', precision, len);
}

