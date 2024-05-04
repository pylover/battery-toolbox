#include <Arduino.h>

#include "acs712.h"


#define ACS712_SAMPLES 10


ACS712::ACS712(int pin, float r1, float r2) {
    this->pin = pin;
    this->coefficient = VREF * 10 * (r1 + r2) / r2 / 1024.0;
    this->offset = 25;
    pinMode(pin, INPUT);
}


    
void 
ACS712::callibrate() {
    int i;
    for (i = 0; i < ACS712_SAMPLES; i++) {
        this->offset += this->get_ampere();
    }
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
    v -= this->offset;
    return v;
}


void
ACS712::print(int precision, int len) {
    float v = this->get_ampere();
    lcd.printu(v, 'A', precision, len);
}

