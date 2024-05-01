#ifndef ACS712_H_
#define ACS712_H_


#include "common.h"


#define ACS712_SAMPLES 3


class ACS712 {
public:
    ACS712(int pin, float coefficient);
    float get_ampere();
    void print(Print *display, int precision, int length);
private:
    int pin;
    float coefficient;
};


#endif  // ACS712_H_
