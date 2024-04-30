#ifndef DIALOG_H_
#define DIALOG_H_


#include "common.h"


class Window: public RotaryConsumer {
public:
    int showwait();
    virtual void show();
    virtual int wait();
};


class Dialog: public Window {
public:
    Dialog(char *first, char *second);
    void pushed() override;
    int rotated(int pos) override;
    void show() override;
    int wait() override;
    static int modal(char * first, char * second);
protected:
    volatile bool waiting;
    const char *first;
    const char *second;
};


class IntegerInputDialog : public Dialog {
public:
    IntegerInputDialog(char * title, int minval, int maxval, int initial);
    void update();
    int rotated(int pos) override;
    static int modal(char * title, int minval, int maxval, int initial);
protected:
    volatile int value;
private:
    int minval;
    int maxval;
};


#endif  // DIALOG_H_
