#ifndef VOLTMETER_H_
#define VOLTMETER_H_


#include "common.h"


#define VOLTMETER_SAMPLES 3


class VoltMeter {
public:
    VoltMeter(int pin, float coefficient);
    float get_voltage();
    void print(Print *display, int precision, int length);
private:
    int pin;
    float coefficient;
};


#endif  // VOLTMETER_H_
