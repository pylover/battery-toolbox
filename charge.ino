#include "charge.h"


int
Charge::main() {
    this->duty = 0;
   
    float v = NumInput<float, char>::show("Cut-off voltage:", 'V', 0, 14, 
            db.discharge.v, 0.1, 1);

    float i = NumInput<float, char>::show("Current:", 'A', 0, 14, 
            db.discharge.i, 0.05, 2);

    if (v != db.discharge.v) {
        db.discharge.v = v;
        db.dirty = true;
    }

    if (i != db.discharge.i) {
        db.discharge.i = i;
        db.dirty = true;
    }

    if (db.dirty) {
        db_commit(&db);
    }

    lcd.clear();
    lcd.print("Charging ");
    int c = 3;
    float d;
    while (this->active) {
        lcd.setCursor(10, 0);
        d = (float)this->duty * 100.0;
        d /= 255;
        printu(&lcd, d, '%', 0, 4);
        lcd.write(' ');
        lcd.write(c-- + CHAR_FULL);
        c = (c + 4) % 4;

        lcd.setCursor(0, 1);
        voltmeter.print(&lcd, 1, 5);
        lcd.write(' ');
        ammeter.print(&lcd, 1, 5);
        lcd.write(' ');
        heatsink.print(&lcd, 0, 4);
        pwm_set(DISCHARGE_PWMPIN, this->duty);
        delay(300);
    }

    digitalWrite(DISCHARGE_PWMPIN, 0);
    return 0;
}
    

int 
Charge::rotated(int pos) {
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
