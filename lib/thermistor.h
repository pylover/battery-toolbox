#ifndef THERMISTOR_H_
#define THERMISTOR_H_


class Thermistor {
public:
    Thermistor(int pin, float thermistor, float resistor, float steinhart[]);
    float get_temp();
private:
    int pin;
    float resistor;
    float thermistor;
    float *steinhart;
};


#endif  // THERMISTOR_H_
