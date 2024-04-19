#ifndef VOLTMETER_H_
#define VOLTMETER_H_


#include "printer.h"


#define VOLTMETER_SAMPLES 3


class VoltMeter: public Printer {
public:
    VoltMeter(int pin, float coefficient);
    float get_voltage();
    int print(Print *display, int precision, int length) override;
private:
    int pin;
    float coefficient;
};


#endif  // VOLTMETER_H_
