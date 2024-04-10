#ifndef DIALOG_H
#define DIALOG_H


#include "common.h"


class Dialog: public RotaryConsumer {
public:
    Dialog(String first, String second);
    void wait();
    void pushed() override;
    int rotated(int amount) override;
    static void show(String first, String second);
private:
    volatile bool waiting;
};


#endif  // DIALOG_H
