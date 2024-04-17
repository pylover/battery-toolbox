#include <Arduino.h>

#include "thermistor.h"


Thermistor::Thermistor(int pin, struct thermistor th, float r) {
	this->pin = pin;
	this->thermistor = th;
	this->resistor = r;
    pinMode(pin, INPUT);
}
    

float
Thermistor::get_temp() {
	/* Steinhart-Hart
	 * https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
	 */
	float v = (float)analogRead(this->pin);
	float resistance = this->resistor * (1023.0 / v - 1.0);
	float logn = log(resistance);
	float logn3 = logn * logn * logn;
	struct thermistor *th = &this->thermistor;
	float t = 1.0 / (th->a + th->b * logn + th->c * logn3);

	/* Convert Kelvin to Celcius */
	t -= 273.15;
	return t;
}
