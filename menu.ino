#include "menu.h"
#include "common.h"


Menu::Menu(LiquidCrystal *p, String title, struct menu_entry items[], 
        unsigned int itemscount) {
    this->lcd = p;
    this->caption = title;
    this->entries = items;
    this->count = itemscount;
    this->current = 0;
}


void
Menu::update() {
    int i;
    lcd->setCursor(0, 1);
    i = lcd->print(entries[current].caption);
    for (; i < 15; i++) {
        lcd->write(' ');
    }

    if ((this->count - current) == 1) {
        lcd->write("^");
    }
    else if (current == 0) {
        lcd->write(CHAR_DOWN);
    }
    else {
        lcd->write(CHAR_UPDOWN);
    }
}


void
Menu::main() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(this->caption);
    update();

    while (true);
}
    

void 
Menu::scroll(int dir) {
    int newindex = current + dir;
    if ((newindex < 0) || (newindex >= count)) {
        return;
    }
    current = newindex;
    update();
}
