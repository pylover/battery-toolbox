#ifndef THERMISTOR_H_
#define THERMISTOR_H_


struct thermistor {
    float resistance;
    /* Steinhart-Hart coefficients can be calculated by
     * https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
     */
    float a;
    float b;
    float c;
};


#define K(v) ((v) * 1000)
#define THERMISTOR_100K_B3950  ((struct thermistor) { \
    K(100),  \
    0.7525536621e-03, \
    2.104606824e-04, \
    1.169355028e-07})


class Thermistor {
public:
    Thermistor(int pin, struct thermistor th, float r);
    float get_temp();
private:
    int pin;
    float resistor;
    struct thermistor thermistor;
};


#endif  // THERMISTOR_H_
