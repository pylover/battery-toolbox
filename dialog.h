#ifndef DIALOG_H_
#define DIALOG_H_


#include "common.h"


class Dialog: public RotaryConsumer {
public:
    void
    pushed() override {
        this->active = false;
    }
    int
    rotated(int pos) override {
        this->active = false;
        return pos;
    }
    virtual int show() {
        while (this->active);
        return 0;
    }
    static int
    modal(class Dialog *dialog) {
        int status;

        lcd.clear();
        rotary.consumer = dialog;
        dialog->active = true;
        status = dialog->show();
        rotary.consumer = NULL;
        return status;
    }
protected:
    volatile bool active;
};


class Message: public Dialog {
public:
    Message(char *title, char *description, melody_t melody) {
        this->title = title;
        this->description = description;
        this->melody = melody;
    }
    int
    show() override {
        lcd.print(this->title);
        lcd.setCursor(0, 1);
        lcd.print(this->description);
        if (this->melody) {
            play(BUZZER, this->melody, &this->active);
        }
        return Dialog::show();
    };
    static void
    modal(char *title, char *description, melody_t melody) {
        Message d(title, description, melody);
        Dialog::modal(&d);
    }
protected:
    char *title;
    char *description;
    melody_t melody;
};


// class Dialog: public Window {
// public:
//     Dialog(char *first, char *second);
//     void show() override;
//     int wait() override;
//     static int modal(char * first, char * second);
// protected:
//     const char *first;
//     const char *second;
// };


// class IntegerInputDialog : public Dialog {
// public:
//     IntegerInputDialog(char * title, int minval, int maxval, int initial);
//     void update();
//     int rotated(int pos) override;
//     static int modal(char * title, int minval, int maxval, int initial);
// protected:
//     volatile int value;
// private:
//     int minval;
//     int maxval;
// };


#endif  // DIALOG_H_
