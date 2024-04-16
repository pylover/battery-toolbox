#ifndef DIALOG_H
#define DIALOG_H


#include "common.h"


class Dialog: public RotaryConsumer {
public:
    Dialog(char *first, char *second);
    void wait();
    void pushed() override;
    int rotated(int amount) override;
    static void show(char * first, char * second);
protected:
    volatile bool waiting;
};


class IntegerInputDialog : public Dialog {
public:
    IntegerInputDialog(char * title, int minval, int maxval, int initial);
    void update();
    int rotated(int amount) override;
    static int show(char * title, int minval, int maxval, int initial);
protected:
    volatile int value;
private:
    int minval;
    int maxval;
};


#endif  // DIALOG_H
