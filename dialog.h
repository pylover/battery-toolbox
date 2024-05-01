#ifndef DIALOG_H_
#define DIALOG_H_


#include "common.h"


class Dialog: public RotaryConsumer {
public:
    virtual void
    pushed() override {
        this->active = false;
    }
    virtual int
    rotated(int pos) override {
        return pos;
    }
    virtual int main() {
        while (this->active);
        return 0;
    }
protected:
    volatile bool active;
    static int
    modal(class Dialog *dialog) {
        int status;

        lcd.clear();
        RotaryConsumer *backup = rotary.consumer;
        rotary.consumer = dialog;
        dialog->active = true;
        status = dialog->main();
        rotary.consumer = backup;
        return status;
    }
};


template <class T>
class Program: public Dialog {
public:
    static int
    show() {
        T d;
        return Dialog::modal(&d);
    }
};


class Message: public Dialog {
public:
    Message(char *title, char *description, melody_t melody) {
        this->title = title;
        this->description = description;
        this->melody = melody;
    }
    int
    main() override {
        lcd.print(this->title);
        lcd.setCursor(0, 1);
        lcd.print(this->description);
        if (this->melody) {
            play(BUZZER, this->melody, &this->active);
        }
        return Dialog::main();
    };
    static void
    show(char *title, char *description, melody_t melody) {
        Message d(title, description, melody);
        Dialog::modal(&d);
    }
protected:
    char *title;
    char *description;
    melody_t melody;
};


template<typename T, typename U>
class NumInput: public Dialog {
public:
    NumInput(char *title, U unit, T minval, T maxval,
            T initial, T step, int precision=0) {
        this->title = title;
        this->unit = unit;
        this->minval = minval;
        this->maxval = maxval;
        this->pos = (int) (initial / step);
        this->precision = precision;
        rotary.setPosition(this->pos);
        this->step = step;
    }
    int
    main() override {
        lcd.print(this->title);
        this->update();
        return Dialog::main();
    };
    int
    rotated(int pos) override {
        int mins = this->minval / this->step;
        int maxs = this->maxval / this->step;

        if (pos == this->pos) {
            return pos;
        }
        else if (pos < mins) {
            pos = mins;
        }
        else if (pos > maxs) {
            pos = maxs;
        }

        this->pos = pos;
        this->update();
        return pos;
    }
    static T
    show(char *title, U unit, T minval, T maxval, T initial, T step,
            int precision=0) {
        NumInput d(title, unit, minval, maxval, initial, step, precision);
        Dialog::modal(&d);
        return d.pos * step;
    }
protected:
    volatile T pos;
    char *title;
    int precision;
    U unit;
    T minval;
    T maxval;
    T step;
    void
    update() {
        lcd.setCursor(0, 1);
        printu(&lcd, this->pos * this->step, this->unit, this->precision, 16);
    }
};


#endif  // DIALOG_H_
