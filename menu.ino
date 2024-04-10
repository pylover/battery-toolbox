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
    int i;
    lcd.setCursor(0, 1);
    lcd.printl(this->entries[this->current].caption);
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


void
Menu::show() {
    this->current = 0;
    lcd.clear();
    lcd.print(this->caption);
    rotary.consumer = this;
    rotary.setPosition(0);
    this->update();
    this->selected = -1;
    while (this->selected < 0);
    rotary.consumer = NULL;
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
