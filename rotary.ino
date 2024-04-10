#include <Arduino.h>
#include "rotary.h"
#include "common.h"


static void
Rotary::isr() {
    rotary.rotated();
}


void
Rotary::rotated() {
    if (this->consumer == NULL) {
        return;
    }
    this->tick();
    int pos = this->getPosition();
    if (pos == this->oldpos) {
        return;
    }
    this->oldpos = pos;
    pos = this->consumer->rotated(pos);
    if (pos == this->oldpos) {
        return;
    }
    this->setPosition(pos);
}


void
Rotary::pushed() {
    if (this->consumer == NULL) {
        return;
    }
    this->consumer->pushed();
}


void
Rotary::begin() {
    attachInterrupt(digitalPinToInterrupt(ROT1), isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROT2), isr, CHANGE);
    
    /* rotary encode push button */
    /* Set PC4 as input */
    DDRC &= ~(1 << DDC4);
    
    /* turn on intrrupt for port c */
    PCICR |= (1 << PCIE1);

    /* turn on pin PC4, which is PCINT12, physical pin 27 */
    PCMSK1 |= (1 << PCINT12);

    this->oldpos = 0;
    this->setPosition(0);
}
