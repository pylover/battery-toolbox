#ifndef MENU_H
#define MENU_H


#include <Arduino.h>

#include <RotaryEncoder.h>
#include "rotary.h"


byte char_down[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
};


byte char_updown[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
};


#define CHAR_UP '^'
#define CHAR_DOWN byte(0)
#define CHAR_UPDOWN byte(1)


struct menu_entry {
    const char *caption;
    void (*func) ();
};


class Menu: public RotaryConsumer {
public:
    Menu(String title, struct menu_entry items[], unsigned int count);
    void update();
    void show();
    volatile int selected;

    void pushed() override;
    int rotated(int amount) override;
private:
    String caption;
    struct menu_entry *entries;
    unsigned int count;
    volatile int current;
};


#endif  // MENU_H
