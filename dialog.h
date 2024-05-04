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
#ifndef DIALOG_H_
#define DIALOG_H_


class Dialog: public RotaryConsumer {
 public:
    virtual void pushed();
    virtual int rotated(int pos);
    virtual int main();
 protected:
    volatile bool active;
    static int modal(class Dialog *dialog);
};


template <class T>
class Program: public Dialog {
 public:
    static int show();
};


class Message: public Dialog {
 public:
    Message(char *title, char *description, struct note *melody);
    int main() override;
    static void show(char *title, char *description, struct note *melody);
 protected:
    char *title;
    char *description;
    struct note *melody;
};


class NumInput: public Dialog {
 public:
    NumInput(char *title, char unit, float minval, float maxval,
            float initial, float step, int precision = 0);
    int main();
    int rotated(int pos) override;
    static float show(char *title, char unit, float minval, float maxval,
            float initial, float step, int precision = 0);
 protected:
    volatile int pos;
    char *title;
    int precision;
    char unit;
    float minval;
    float maxval;
    float step;
    void update();
};


#endif  // DIALOG_H_
