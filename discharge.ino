#include "discharge.h"


int
Discharge::main() {
    this->duty = 0;
   
    float v = NumInput<float, char>::show("Cut-off voltage:", 'V', 0, 14, 
            db.discharge.v, 0.1, 1);

    float c = NumInput<float, char>::show("Current:", 'A', 0, 14, 
            db.discharge.i, 0.05, 2);

    if (v != db.discharge.v) {
        db.discharge.v = v;
        db.dirty = true;
    }

    if (c != db.discharge.i) {
        db.discharge.i = c;
        db.dirty = true;
    }

    if (db.dirty) {
        db_commit(&db);
    }

    lcd.clear();
    while (this->active) {
        lcd.setCursor(0, 0);
        lcd.print("Discharging ");
        heatsink.print(&lcd, 0, 4);
        // lcd.fill(' ', dutyloc + lcd.print(this->duty));
        lcd.setCursor(0, 1);
        voltmeter.print(&lcd, 1, 5);
        lcd.write(' ');
        ammeter.print(&lcd, 1, 5);
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
