#include "backlight.h"
#include "config.h"

#include <avr/io.h>

void backlight__init(void)
{
	DDR(BACKLIGHT_PORT) |= (1 << BACKLIGHT_PIN);

	/* initialize timer 2 */
	TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS22);
}

void backlight__update(void)
{
	;
}

void backlight__set_brightness(uint8_t b)
{
	OCR2 = b;
}

