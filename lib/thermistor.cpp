#include <Arduino.h>

#include "thermistor.h"


Thermistor::Thermistor(int pin, float thermistor, float resistor, 
		float *steinhart) {
	this->pin = pin;
	this->thermistor = thermistor;
	this->resistor = resistor;
	this->steinhart = steinhart;
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
	float a = this->steinhart[0];
	float b = this->steinhart[1];
	float c = this->steinhart[2];
	float t = 1.0 / (a + b * logn + c * logn3);

	/* Convert Kelvin to Celcius */
	t -= 273.15;
	return t;
}
