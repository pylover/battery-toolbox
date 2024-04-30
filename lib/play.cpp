#include <Arduino.h>

#include "play.h"


void
play(int pin, float notes[]) {
    int i = 0;

    while (notes[i]) {
        tone(pin, notes[i++]);
        delay(notes[i++]);
        noTone(pin);
    }
}
