#include "charge.h"


int
Charge::main() {
    int oldduty = 0;
    this->duty = 0;
   
    float v = NumInput::show("Cut-off voltage:", 'V', 0, 14, db.discharge.v, 
            0.1, 1);

    float i = NumInput::show("Current:", 'A', 0, 14, db.discharge.i, 0.05, 2);

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
    pwm_set(DISCHARGE_PWMPIN, this->duty);
    int c = 3;
    float d;
    while (this->active) {
        /* Animation */
        lcd.setCursor(0, 0);
        lcd.write(c-- + CHAR_FULL);
        lcd.write("C");
        c = (c + 4) % 4;

        /* Duty Cycle */
        lcd.setCursor(3, 0);
        d = (float)this->duty * 100.0;
        d /= 255;
        lcd.printu(d, '%', 1, 6);
      
        /* Temperature */
        lcd.setCursor(10, 0);
        heatsink.print(1, 6);

        /* Voltage */
        lcd.setCursor(0, 1);
        vmeter.printdiff(2, 9);

        /* Current */
        lcd.setCursor(10, 1);
        ammeter.print(1, 6);

        if (oldduty != this->duty) {
            pwm_set(DISCHARGE_PWMPIN, this->duty);
            oldduty = this->duty;
        }
        delay(500);
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
