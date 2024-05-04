#ifndef VOLTMETER_H_
#define VOLTMETER_H_


#include "common.h"


#define VOLTMETER_SAMPLES 5


class VoltMeter {
public:
    VoltMeter(int pinh, int pinl, float r1, float r2);
    float vhigh();
    float vlow();
    float vdiff();
    void print(Print *display, int precision, int length);
private:
    int pinh;
    int pinl;
    float coefficient;
};


#endif  // VOLTMETER_H_
