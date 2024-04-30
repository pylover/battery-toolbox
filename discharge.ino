#include "discharge.h"


int
Discharge::main() {
    this->duty = 0;
    dutyloc = lcd.print("Discharging ");
    while (this->active) {
        lcd.setCursor(dutyloc, 0);
        lcd.fill(' ', dutyloc + lcd.print(this->duty));
        lcd.setCursor(0, 1);
        voltmeter.print(&lcd, 1, 5);
        lcd.write(' ');
        ammeter.print(&lcd, 2, 6);
        lcd.write(' ');
        heatsink.print(&lcd, 0, 3);
        pwm_set(DISCHARGE_PWMPIN, this->duty);
        delay(200);
    }
    digitalWrite(DISCHARGE_PWMPIN, 0);
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
