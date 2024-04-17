# Battery Toolbox

## Features
- Charge and discharge with programmable thresholds.
- Programmable (dis)charging voltage.
- Programmable (dis)changing current.
- Resume the (dis)charge programm after power cut-off.


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
