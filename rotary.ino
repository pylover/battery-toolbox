#include "rotary.h"


void
Rotary::begin() {
    attachInterrupt(digitalPinToInterrupt(ROT1), joy_rotated, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROT2), joy_rotated, CHANGE);
    
    /* rotary encode push button */
    /* Set PC4 as input */
    DDRC &= ~(1 << DDC4);
    
    /* turn on intrrupt for port c */
    PCICR |= (1 << PCIE1);

    /* turn on pin PC4, which is PCINT12, physical pin 27 */
    PCMSK1 |= (1 << PCINT12);
}
