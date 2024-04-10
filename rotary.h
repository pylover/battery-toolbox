#ifndef ROTARY_H
#define ROTARY_H


#include <RotaryEncoder.h>


#define ROT1 2
#define ROT2 3
#define ROTSW A4


class RotaryConsumer {
public:
    virtual int rotated(int amount);
    virtual void pushed();
};


class Rotary : public RotaryEncoder {
public:
    Rotary(): RotaryEncoder(ROT1, ROT2, RotaryEncoder::LatchMode::FOUR3) {};
    void begin();
    void pushed();
    RotaryConsumer *consumer = NULL;
private:
    void rotated();
    static void isr();
};


#endif  // ROTARY_H