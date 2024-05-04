#include "dialog.h"
    

void
Dialog::pushed() {
    this->active = false;
}


int
Dialog::rotated(int pos) {
    return pos;
}


int 
Dialog::main() {
    while (this->active);
    return 0;
}
    

static int
Dialog::modal(class Dialog *dialog) {
    int status;

    lcd.clear();
    RotaryConsumer *backup = rotary.consumer;
    rotary.consumer = dialog;
    dialog->active = true;
    status = dialog->main();
    rotary.consumer = backup;
    return status;
}
    


template<class T>
static int
Program<T>::show() {
    T d;
    return Dialog::modal(&d);
}



Message::Message(char *title, char *description, struct note *melody) {
    this->title = title;
    this->description = description;
    this->melody = melody;
}


int
Message::main() {
    lcd.print(this->title);
    lcd.setCursor(0, 1);
    lcd.print(this->description);
    if (this->melody) {
        play(BUZZER, this->melody, &this->active);
    }
    return Dialog::main();
};


static void
Message::show(char *title, char *description, struct note *melody) {
    Message d(title, description, melody);
    Dialog::modal(&d);
}


template<typename T, typename U>
NumInput<T, U>::NumInput(char *title, U unit, T minval, T maxval, T initial, T step, 
        int precision=0) {
    this->title = title;
    this->unit = unit;
    this->minval = minval;
    this->maxval = maxval;
    this->pos = (int) (initial / step);
    this->precision = precision;
    rotary.setPosition(this->pos);
    this->step = step;
}


template<typename T, typename U>
int
NumInput<T, U>::main() {
    lcd.print(this->title);
    this->update();
    return Dialog::main();
};


template<typename T, typename U>
int
NumInput<T, U>::rotated(int pos) {
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


template<typename T, typename U>
static T
NumInput<T, U>::show(char *title, U unit, T minval, T maxval, T initial, 
        T step, int precision=0) {
    NumInput d(title, unit, minval, maxval, initial, step, precision);
    Dialog::modal(&d);
    return d.pos * step;
}
    

template<typename T, typename U>
void
NumInput<T, U>::update() {
    lcd.setCursor(0, 1);
    printu(&lcd, this->pos * this->step, this->unit, this->precision, 16);
}
