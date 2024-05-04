#ifndef ACS712_H_
#define ACS712_H_


#include "common.h"


class ACS712 {
public:
    ACS712(int pin, float r1, float r2);
    float get_ampere();
    void print(int precision, int len);
    void callibrate();
private:
    int pin;
    float offset;
    float coefficient;
};


#endif  // ACS712_H_
