#ifndef VOLTMETER_H_
#define VOLTMETER_H_


#include "common.h"


#define VOLTMETER_SAMPLES 5


class VoltMeter {
public:
    VoltMeter(int pin, float r1, float r2);
    float get_voltage();
    void print(Print *display, int precision, int length);
private:
    int pin;
    float coefficient;
};


#endif  // VOLTMETER_H_
