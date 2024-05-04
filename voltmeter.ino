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
