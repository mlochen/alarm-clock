#include "lightsens.h"
#include "config.h"

#include <avr/io.h>

void lightsens__init(void)
{
	/* initialize the ADC */
	ADMUX = (1 << ADLAR) | LIGHTSENS_ADC;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADFR) |
		     (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void lightsens__update(void)
{
	;
}

uint8_t lightsens__get_brightness(void)
{
	return ADCH;
}

