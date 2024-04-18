#include "printer.h"


int
Printer::print_unit(Print *display, float value, int precision, char *unit) {
    return display->print(value, precision) + display->print(unit);
}


int
Printer::print_unit(Print *display, float value, int precision, byte unit) {
    return display->print(value, precision) + display->write(unit);
}
