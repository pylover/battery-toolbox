#ifndef ACS712_H_
#define ACS712_H_


#include "printer.h"


#define ACS712_SAMPLES 3


class ACS712: public Printer {
public:
    ACS712(int pin, float coefficient);
    float get_ampere();
    int print(Print *display, int precision, int length) override;
private:
    int pin;
    float coefficient;
};


#endif  // ACS712_H_
