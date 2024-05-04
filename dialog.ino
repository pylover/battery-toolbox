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


NumInput::NumInput(char *title, char unit, float minval, float maxval, 
        float initial, float step, int precision=0) {
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
NumInput::main() {
    lcd.print(this->title);
    this->update();
    return Dialog::main();
};


int
NumInput::rotated(int pos) {
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


static float
NumInput::show(char *title, char unit, float minval, float maxval, 
        float initial, float step, int precision=0) {
    NumInput d(title, unit, minval, maxval, initial, step, precision);
    Dialog::modal(&d);
    return d.pos * step;
}
    

void
NumInput::update() {
    lcd.setCursor(0, 1);
    lcd.printu(this->pos * this->step, this->unit, this->precision, 16);
}
