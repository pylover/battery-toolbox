#include <avr/interrupt.h>

#include <LiquidCrystal.h>
#include <RotaryEncoder.h>


#define PROJECT "Battery Toolbox"
#define VERSION "0.1.0a"
#define VVERSION "v"VERSION"(pylover)"


/* lcd pinout */
#define LCD_RS 12 
#define LCD_EN 11 
#define LCD_D4 10 
#define LCD_D5 9 
#define LCD_D6 8 
#define LCD_D7 7
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/* rotary encoder pinout */
#define ROT1 2
#define ROT2 3
#define ROTSW A4 
RotaryEncoder joy = RotaryEncoder(ROT1, ROT2, 
        RotaryEncoder::LatchMode::FOUR3);


#define info Serial.println


void 
joy_rotated() {
    joy.tick();
}


ISR(PCINT1_vect) {
    int v = analogRead(ROTSW);
    if (v < 1000) {
        return;
    }
    info("Rotary Push");
}


void 
setup() {
    Serial.begin(115200);
    while (!Serial);
    info();
    info(PROJECT);
    info(VVERSION);
    info();

    /* display settings */
    lcd.begin(16, 2);
    lcd.noAutoscroll();

    /* rotary encoder */
    /* turn on intruupt for port c */
    PCICR |= (1 << PCIE1);

    /* turn on pin PC4, which is PCINT12, physical pin 27 */
    PCMSK1 |= (1 << PCINT12);

    /* enable pull-up on PC4 */
    PORTC |= (1 << PC4);
    DDRC |= (1 << DDC4);

    attachInterrupt(digitalPinToInterrupt(ROT1), joy_rotated, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROT2), joy_rotated, CHANGE);
}


void 
loop() {
    /* Greeting */
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(PROJECT);
    lcd.setCursor(0, 1);
    lcd.print(VVERSION);

    // while (true);
    // delay(1000);
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("What to do?");

    static int pos = 0;
    joy.tick(); // just call tick() to check the state.
    while (true) {
        int newPos = joy.getPosition();
        if (pos != newPos) {
            Serial.print("pos:");
            Serial.print(newPos);
            Serial.print(" dir:");
            info((int)(joy.getDirection()));
            pos = newPos;
        }
    }
}
