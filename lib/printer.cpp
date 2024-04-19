#include "printer.h"


static char buffer[16];


int
Printer::print_unit(Print *display, float value, int precision, char *unit, 
        int length) {
    String v = dtostrf(value, length - strlen(unit), precision, buffer);
    return display->print(v) + display->print(unit);
}


int
Printer::print_unit(Print *display, float value, int precision, byte unit, 
        int length) {
    String v = dtostrf(value, length - 1, precision, buffer);
    return display->print(v) + display->write(unit);
}
