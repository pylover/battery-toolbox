#ifndef COMMON_H_
#define COMMON_H_


#include <Arduino.h>


#define PROJECT "Battery Toolbox"
#define VERSION "0.1.0a"
#define VVERSION "v"VERSION"(pylover)"


#define VREF    4.8
#define infoln Serial.println
#define info Serial.print


void
pwm_set(int pin, int duty) {
    analogWrite(pin, duty);
    TCCR1B = TCCR1B & B11100000 | B00001001;
}


#endif  // COMMON_H_
