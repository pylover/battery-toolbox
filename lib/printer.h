#ifndef PRINTER_H_
#define PRINTER_H_


#include <Arduino.h>


class Printer {
public:
    int print_unit(Print *display, float value, int precision, char *unit);
    int print_unit(Print *display, float value, int precision, byte unit);
    virtual int print(Print *display, int precision);
};


#endif  // PRINTER_H_
