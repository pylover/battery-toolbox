#include <Arduino.h>
#include "menu.h"
#include "common.h"


Menu::Menu(String title, struct menu_entry items[], unsigned int itemscount) {
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
    this->current = 0;
    lcd.clear();
    lcd.print(this->caption);
    rotary.consumer = this;
    this->selected = -1;
    rotary.setPosition(0);
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
