#ifndef ROTARY_H
#define ROTARY_H


#include <RotaryEncoder.h>


#define ROT1 2
#define ROT2 3
#define ROTSW A4


class Rotary : public RotaryEncoder {
public:
    Rotary(): RotaryEncoder(ROT1, ROT2, RotaryEncoder::LatchMode::FOUR3) {};
    void Rotary::begin();
};


#endif  // ROTARY_H
