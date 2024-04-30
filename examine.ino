#include "examine.h"


// void
// Examine::show() {
//     Window::show();
//     lcd.write("Examination");
// }
// 
// 
// int
// Examine::wait() {
//     int i;
//     this->waiting = true;
//     while (this->waiting) {
//         lcd.setCursor(0, 1);
//         voltmeter.print(&lcd, 1, 5);
//         lcd.write(' ');
//         ammeter.print(&lcd, 2, 6);
//         lcd.write(' ');
//         heatsink.print(&lcd, 0, 3);
//         delay(500);
//     }
//     Window::close();
//     return 0;
// }
//     
// 
// int 
// Examine::rotated(int pos) {
//     return pos;
// }
// 
// 
// void 
// Examine::pushed() {
//     this->waiting = false;
// }
