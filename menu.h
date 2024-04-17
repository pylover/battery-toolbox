#ifndef MENU_H
#define MENU_H


#include <Arduino.h>

#include <RotaryEncoder.h>
#include "rotary.h"


#define ENTRYCOUNT(a) (sizeof(a) / sizeof (struct menu_entry))


struct menu_entry {
    const char *caption;
    void (*func) ();
};


class Menu: public RotaryConsumer {
public:
    Menu(String title, struct menu_entry items[], unsigned int count);
    void update();
    struct menu_entry* show();

    void pushed() override;
    int rotated(int pos) override;

private:
    String caption;
    struct menu_entry *entries;
    unsigned int count;
    volatile int current;
    volatile int selected;
};


#endif  // MENU_H
