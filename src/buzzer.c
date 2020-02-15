#include "buzzer.h"
#include "config.h"

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

static uint8_t cycle_count;
static bool active;

void buzzer__init(void)
{
	DDR(BUZZER_PORT) |= (1 << BUZZER_PIN);
}

void buzzer__update(void)
{
	if (active)
	{
		if (cycle_count < 5)
		{
			PORT(BUZZER_PORT) |= (1 << BUZZER_PIN);
		}
		else
		{
			PORT(BUZZER_PORT) &= ~(1 << BUZZER_PIN);
		}

		cycle_count++;
		if (cycle_count >= 100)
		{
			cycle_count = 0;
		}
	}
}

void buzzer__activate(void)
{
	active = true;
	cycle_count = 0;
}

void buzzer__deactivate(void)
{
	active = false;
}	

