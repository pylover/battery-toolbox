#include <avr/interrupt.h>

#include "thermistor.h"

#include "common.h"
#include "menu.h"
#include "display.h"
#include "rotary.h"
#include "dialog.h"


static Display lcd;
static Rotary rotary;
static struct menu_entry actions[] = {
    {"Examine", NULL},
    {"Foo", NULL},
    {"Bar", NULL},
    {"Baz", NULL},
    {"qux", NULL},
    {"quux", NULL},
};


static Menu menu("Main menu:", actions, ENTRYCOUNT(actions));
#define K(v) ((v) * 1000)

/* Steinhart coefficients are calculated by 
 * https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
  */
static Thermistor therm1(A2, K(100), K(4.7), 
        (float[]){0.7525536621e-03, 2.104606824e-04, 1.169355028e-07});


ISR(PCINT1_vect) {
    if (PINC & (1 << PINC4)) {
        rotary.pushed();
    }
}


void 
setup() {
    Serial.begin(115200);
    while (!Serial);
    infoln();
    infoln(PROJECT);
    infoln(VVERSION);
    infoln();

    rotary.begin();
    lcd.begin();

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    // analogReference(INTERNAL);
    analogReference(EXTERNAL);
}

// #define RES (((float)30) / ((float)1024))
#define RES 0.3

void 
loop() {
    int adcval;
    double v;
    struct menu_entry *prog;

    // /* Greeting */
    // Dialog::show(PROJECT, VVERSION);

    /* A meter */
    // /* Calibrate */
    // int adcval_last = 0;
    // int offset;
    // Serial.print("Calibrating ACS712 ...");
    // while (true) {
    //     adcval = analogRead(A1);
    //     if (adcval_last == adcval) {
    //         break;
    //     }
    //     adcval_last = adcval;
    //     offset = 512 - adcval;
    //     Serial.print("adc val: ");
    //     Serial.println(adcval);
    //     Serial.print("offset: ");
    //     Serial.println(offset);
    //     delay(100);
    // }
    // Serial.print("Calibration done");
    
    // #define MAX(a, b) (a > b? a: b)
    // Serial.print("Calibrating ACS712 ...");
    // adcval = analogRead(A1);
    // delay(10);
    // adcval = max(adcval, analogRead(A1));
    // delay(10);
    // int offset = max(adcval, analogRead(A1));
    // Serial.print("Calibration done");
    // int offset = 507;

    // while (true) {
    //     adcval = analogRead(A1);
    //     delay(10);
    //     adcval = max(adcval, analogRead(A1));
    //     delay(10);
    //     adcval = max(adcval, analogRead(A1));
    //     lcd.clear();
    //     lcd.print(adcval);
    //     adcval -= offset;
    //     // Serial.print("adc val: ");
    //     // Serial.println(adcval);
    //     v = ((double)adcval) * ((double)0.049);
    //     // v -= 25;
    //     Serial.println(v);
    //     lcd.setCursor(0, 1);
    //     lcd.print(v, 2);
    //     lcd.write('A');
    //     delay(500);
    // }

    while (true) {
        float temp1 = therm1.get_temp();

        /* Print temperature in port serial */
        Serial.print("temperature: ");
        Serial.println(temp1, 3);
        delay(500);
    }
  
    int duty = 0;
    while (true) {
        analogWrite(10, duty); 
        analogWrite(9, duty); 
        Serial.println(duty);
        /* for PWM frequency of ~62K Hz */
        TCCR1B = TCCR1B & B11100000 | B00001001; 
        
        duty = IntegerInputDialog::show("Duty Cycle:", 0, 255, duty);
    }

    /* Battery Voltage */
    while (true) {
        adcval = analogRead(A0);
        v = ((double)adcval) * ((double)0.016);
        Serial.println(v);
        lcd.clear();
        lcd.print(adcval);
        lcd.setCursor(0, 1);
        lcd.print(v, 2);
        lcd.write('V');
        delay(500);
    }

    while (true) {
        /* Main menu */
        prog = menu.show();
        
        /* Selected */
        Dialog::show("Selected: ", prog->caption);
    }
    while (true);
}
