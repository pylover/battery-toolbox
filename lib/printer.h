#ifndef PRINTER_H_
#define PRINTER_H_


#include <Arduino.h>


class Printer {
public:
    int print_unit(Print *display, float value, int precision, char *unit,
            int length);
    int print_unit(Print *display, float value, int precision, byte unit,
            int length);
    virtual int print(Print *display, int precision, int length);
};


#endif  // PRINTER_H_
