#ifndef MENU_H
#define MENU_H


#include <Arduino.h>


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


class Menu {
public:
    Menu(String title, struct menu_entry items[], unsigned int count);
    void Menu::update();
    void Menu::main();
    void Menu::scroll(int count);
private:
    String caption;
    struct menu_entry *entries;
    unsigned int count;
    int current;
};


#endif  // MENU_H
