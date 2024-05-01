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


template<typename T, typename U>
void
printu(Print *display, T val, U unit, int precision, int maxlen) {
    int tmp;
    int p = pow(10, precision);
    char r = 0;

    /* Reduce maxlen to freeup space for unit */
    maxlen--;

    /* unit and ratio */
    if (val < 1) {
        if (val < .000001) {
            val *= 1000000000;
            r = 'n';
        }
        else if (val < .001) {
            val *= 1000000;
            r = 'u';
        }
        else {
            val *= 1000;
            r = 'm';
        }
        maxlen--;
    }

    /* round */
    tmp = (int) (val * p);
    val = ((T) tmp) / p;

    char buffer[maxlen];
    String v = dtostrf(val, maxlen, precision, buffer);
    display->print(v);
    if (r) {
        display->write(r);
    }
    display->write(unit);
}


#endif  // COMMON_H

