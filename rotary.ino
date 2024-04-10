#include "rotary.h"


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
    int pos = this->consumer->rotated(this->getPosition());
    this->setPosition(pos);
}


void
Rotary::pushed() {
    if (this->consumer == NULL) {
        return;
    }
    this->consumer->pushed();
    // if (status & S_SPLASH) {
    //     status = S_MENU;
    //     return;
    // }
    // infoln("Rotary Push");
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
}
