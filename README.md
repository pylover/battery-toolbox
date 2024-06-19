# Battery Toolbox

## Features
- Charge and discharge with programmable thresholds.
- Programmable (dis)charging voltage.
- Programmable (dis)changing current.
- Resume the (dis)charge programm after power cut-off.


## Charge circuit
```
 +-----------------+
 | Battery Toolbox |
 |                 |
 |           Load+ > Not Connected
 |           Load- > Not Connected
 |                 |
 |            BAT+ >---> To battery
 |            BAT- >---> To battery
 +-----------------+
```


## Discharge circuit
```
 +-----------------+
 | Battery Toolbox |
 |                 |
 |           Load+ >------|0Ω22|--+
 |                 |              |
 |           Load- >--------------+
 |                 |
 |            BAT+ >---> To battery
 |            BAT- >---> To battery
 +-----------------+


VBAT: 14 (max)
RLOAD: 2.2Ω 100W
RMOSFET: 3mΩ

MAXI: VBAT / (RLOAD + RMOSFET) = 6.35A
MAXW: VBAT * MAXI = 88.89W
VRLOAD: VBAT * RLOAD / (RLOAD + RMOSFET) = 13.9V
WRLOAD: RLOAD * (MAXI ^ 2)
MAXMOSFETW: (VBAT - VRLOAD) * MAXI = 0.12W
```

## Let's cook

### What you need:
- One `Arduino Uno`
- TODO: circuit

### Setup build system
Install [Arduino CLI](https://arduino.github.io/arduino-cli/0.35/). Then,

```bash
make env
```

### Compile
```bash
make all
```

### Flash the board
```bash
make flash
```

## References

- https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm/
- https://www.allaboutcircuits.com/technical-articles/low-pass-filter-a-pwm-signal-into-an-analog-voltage/
- https://docs.arduino.cc/learn/programming/eeprom-guide/
- https://docs.arduino.cc/learn/built-in-libraries/eeprom/
- https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
