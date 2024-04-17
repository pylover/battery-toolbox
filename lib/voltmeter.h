#ifndef VOLTMETER_H_
#define VOLTMETER_H_


#define VOLTMETER_SAMPLES 3


class VoltMeter {
public:
    VoltMeter(int pin, float coefficient);
    float get_voltage();
    int print(Print *display, int precision);
private:
    int pin;
    float coefficient;
};


#endif  // VOLTMETER_H_
