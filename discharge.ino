#include "discharge.h"


int
Discharge::main() {
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
    lcd.print("Discharging ");
    char c = 0;
    while (this->active) {
        lcd.setCursor(15, 0);
        lcd.write(c++ + CHAR_FULL);
        c %= 4;

        lcd.setCursor(0, 1);
        // lcd.fill(' ', dutyloc + lcd.print(this->duty));
        vmeter.print(1, 5);
        lcd.write(' ');
        ammeter.print(1, 5);
        lcd.write(' ');
        heatsink.print(0, 4);
        pwm_set(DISCHARGE_PWMPIN, this->duty);
        delay(300);
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
