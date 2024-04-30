#ifndef COMMON_H
#define COMMON_H


#include <Arduino.h>


#define PROJECT "Battery Toolbox"
#define VERSION "0.1.0a"
#define VVERSION "v"VERSION"(pylover)"


#define infoln Serial.println
#define info Serial.print


void
pwm_set(int pin, int duty) {
    analogWrite(pin, duty);
    TCCR1B = TCCR1B & B11100000 | B00001001;
}


#define BUZZER 6
#define buzz(f) tone(BUZZER, f)
#define nobuzz() noTone(BUZZER)
#define buzzwait(f, i) buzz(1000); delay(i); nobuzz()


#endif  // COMMON_H

