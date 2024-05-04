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
#include <Arduino.h>
#include "menu.h"
#include "common.h"


Menu::Menu(const char *title, struct menu_entry items[], 
        unsigned int itemscount) {
    this->caption = title;
    this->entries = items;
    this->count = itemscount;
    this->current = 0;
    this->selected = -1;
}


void
Menu::update() {
    int i = 0;
    lcd.setCursor(0, 1);
    i += lcd.print(this->current + 1);
    i += lcd.print(". ");
    i += lcd.print(this->entries[this->current].caption);
    lcd.fill(' ', i);
    lcd.setCursor(15, 1);
    if ((this->count - this->current) == 1) {
        lcd.write(CHAR_UP);
    }
    else if (this->current == 0) {
        lcd.write(CHAR_DOWN);
    }
    else {
        lcd.write(CHAR_UPDOWN);
    }
}


struct menu_entry* 
Menu::show() {
    lcd.clear();
    lcd.print(this->caption);
    rotary.consumer = this;
    this->selected = -1;
    rotary.setPosition(this->current);
    this->update();
    while (this->selected < 0);
    rotary.consumer = NULL;
    return &this->entries[this->selected];
}
    

void 
Menu::pushed() {
    this->selected = this->current;
}


int 
Menu::rotated(int pos) {
    if ((pos < 0) || (pos >= this->count)) {
        return this->current;
    }
    this->current = pos;
    this->update();
    return pos;
}
