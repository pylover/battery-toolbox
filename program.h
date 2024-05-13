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
#ifndef PROGRAM_H_
#define PROGRAM_H_


#include "dialog.h"


#define MAX_CURRENT 10
#define COOLING_STEPDOWN 20
#define VOLTAGE_STEP 0.1
#define CURRENT_STEP 0.05


enum mosfet_status {
    CS_PASSING,
    CS_COOLING,
    CS_DONE,
};



class Program: public Dialog {
 public:
     int main() override;
     int rotated(int pos) override;
     void printstatus(float t, float c, float sv, float lv);
 protected:
     volatile int duty = 0;
     volatile int risk = 0;
     float current_threshold;
     float voltage_threshold;
     enum mosfet_status status;
     void ask();
     int mosfet(int d);
     virtual void tick(unsigned long ticks, float t, float c, float sv,
             float lv);
     virtual float sourcevoltage_get();
     virtual float loadvoltage_get();
     virtual void prepare();
     virtual void terminate();
     virtual struct watt * dbentry_get();
     virtual bool completed(float sv, float lv);
     virtual char * title_get();
};


#endif  // PROGRAM_H_
