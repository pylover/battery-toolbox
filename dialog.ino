#include "dialog.h"


// Dialog::Dialog(char *first, char *second) {
//     this->first = first;
//     this->second = second;
// }
// 
// 
// int
// Dialog::wait() {
//     while (this->waiting);
//     Window::close();
//     return 0;
// }
// 
// 
// static int
// Dialog::modal(char * first, char * second) {
//     Dialog *d = new Dialog(first, second);
//     int status = d->showwait();
//     delete d;
//     return status;
// }



// IntegerInputDialog::IntegerInputDialog(char * title, int minval, int maxval, 
//             int initial): Dialog(title, NULL) {
//     this->minval = minval;
//     this->maxval = maxval;
//     this->value = initial;
//     rotary.setPosition(initial);
//     this->update();
// }
// 
// 
// void
// IntegerInputDialog::update() {
//     lcd.setCursor(0, 1);
//     int i = lcd.print(this->value);
//     lcd.fill(' ', i);
// }
// 
// 
// static int 
// IntegerInputDialog::modal(char * title, int minval, int maxval, int initial) {
//     IntegerInputDialog *d = new IntegerInputDialog(title, minval, maxval, 
//             initial);
//     d->showwait();
//     int value = d->value;
//     delete d;
//     return value;
// }
// 
// 
// int 
// IntegerInputDialog::rotated(int pos) {
//     if (pos == this->value) {
//         return pos;
//     }
//     else if (pos < this->minval) {
//         pos = this->minval;
//     }
//     else if (pos > this->maxval) {
//         pos = this->maxval;
//     }
// 
//     this->value = pos;
//     this->update();
//     this->waiting = false;
//     return pos;
// }
