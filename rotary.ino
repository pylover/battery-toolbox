/*
Copyright (c) 2024, Vahid Mardani <vahid.mardani@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation  and/or other materials provided with the distribution.
3. Neither the names of the copyright holders nor the names of any
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#include <Arduino.h>
#include "rotary.h"
#include "common.h"


static void
Rotary::isr() {
    rotary.rotated();
}


Rotary::Rotary(): RotaryEncoder(ROT1, ROT2, RotaryEncoder::LatchMode::FOUR3) {
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
