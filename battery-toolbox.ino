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


#define S_SPLASH 1
#define S_MENU (1 << 1)


static volatile int status = S_SPLASH;


byte char_up[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
};


byte char_down[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
};


byte char_updown[8] = {
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
};

#define CHAR_UP byte(0)
#define CHAR_DOWN byte(1)
#define CHAR_UPDOWN byte(2)

void 
joy_rotated() {
    joy.tick();
}


void
joy_pushed() {
    info("Rotary Push");
}


ISR(PCINT1_vect) {
    int v = analogRead(ROTSW);
    // Serial.print(v);
    // info();
    if (v < 100) {
        return;
    }
    if (status & S_SPLASH) {
        status = S_MENU;
        return;
    }
    joy_pushed();
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
    lcd.createChar(0, char_up);
    lcd.createChar(1, char_down);
    lcd.createChar(2, char_updown);

    /* rotary encoder */
    attachInterrupt(digitalPinToInterrupt(ROT1), joy_rotated, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROT2), joy_rotated, CHANGE);
   
    /* rotary encode push button */

    /* Set PC4 as input */
    DDRC &= ~(1 << DDC4);
    
    /* turn on intrrupt for port c */
    PCICR |= (1 << PCIE1);

    /* turn on pin PC4, which is PCINT12, physical pin 27 */
    PCMSK1 |= (1 << PCINT12);
}


void 
loop() {
    /* Greeting */
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(PROJECT);
    lcd.setCursor(0, 1);
    lcd.print(VVERSION);

    while (status & S_SPLASH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("What to do?");
    lcd.setCursor(0, 1);
    lcd.write(CHAR_UP);
    lcd.write(CHAR_DOWN);
    lcd.write(CHAR_UPDOWN);

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
