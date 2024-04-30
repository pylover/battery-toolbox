#include "discharge.h"


void
Discharge::show() {
    lcd.clear();
}


int
Discharge::wait() {
    int i;
    i = lcd.print("Discharging ");
    this->waiting = true;
    while (this->waiting) {
        lcd.setCursor(i, 0);
        lcd.fill(' ', i + lcd.print(this->duty));
        lcd.setCursor(0, 1);
        voltmeter.print(&lcd, 1, 5);
        lcd.write(' ');
        ammeter.print(&lcd, 2, 6);
        lcd.write(' ');
        heatsink.print(&lcd, 0, 3);
        pwm_set(DISCHARGE_PWMPIN, this->duty);
        delay(500);
    }
    return 0;
}
    

int 
Discharge::rotated(int pos) {
    if (pos < 0) {
        this->duty = 0;
    }
    else if (pos > 255) {
        this->duty = 255;
    }
    else {
        this->duty = pos;
    }
    return this->duty;
}


void 
Discharge::pushed() {
    this->waiting = false;
}