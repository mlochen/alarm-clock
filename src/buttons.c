#include "buttons.h"
#include "config.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DEBOUNCE_CYCLES 	5

static void (*press[3])(void);
static void (*release[3])(void);
static void (*hold[3])(void);
static uint8_t active_count[3];

void buttons__init(void)
{
	/* buttons are inputs */
	DDR(BUTTON1_PORT) &= ~(1 << BUTTON1_PIN);
	DDR(BUTTON2_PORT) &= ~(1 << BUTTON2_PIN);
	DDR(BUTTON3_PORT) &= ~(1 << BUTTON3_PIN);

	/* enable pull up resistors */
	PORT(BUTTON1_PORT) |= (1 << BUTTON1_PIN);
	PORT(BUTTON2_PORT) |= (1 << BUTTON2_PIN);
	PORT(BUTTON3_PORT) |= (1 << BUTTON3_PIN);
}

void buttons__update(void)
{
	bool pressed[3];
	
	pressed[0] = (PIN(BUTTON1_PORT) & (1 << BUTTON1_PIN)) == 0;
	pressed[1] = (PIN(BUTTON2_PORT) & (1 << BUTTON2_PIN)) == 0;
	pressed[2] = (PIN(BUTTON3_PORT) & (1 << BUTTON3_PIN)) == 0;

	for (uint8_t i = 0; i < 3; i++)
	{
		/* the press event fires when the button state changes from unpressed
		 * to pressed */
		if (pressed[i] && active_count[i] == 0)
		{
			if (press[i] != NULL)
			{
				(*press[i])();
			}
		}

		/* the release event fires when the button is released after less than
		 * a second */
		if (!pressed[i] &&
			active_count[i] >= DEBOUNCE_CYCLES && active_count[i] < 100)
		{
			if (release[i] != NULL)
			{
				(*release[i])();
			}
		}

		/* the hold event fires when the button was held for one second and
		 * then every 250ms the button is kept pressed */
		if (pressed[i] && active_count[i] == 100)
		{
			if (hold[i] != NULL)
			{
				(*hold[i])();
			}
		}

		if (pressed[i])
		{
			active_count[i]++;
		}
		else
		{
			/* consider the button as pressed even if it is not for the first
			 * few cycles */
			if (active_count[i] > 0 && active_count[i] < DEBOUNCE_CYCLES)
			{
				active_count[i]++;
			}
			else
			{
				active_count[i] = 0;
			}
		}

		/* after 1.25s reset the counter to 100. this enables the repeated
		 * firing of the hold event */
		if (active_count[i] >= 125)
		{
			active_count[i] = 100;
		}
	}
}

void buttons__set_press_event(uint8_t button, void (*f)(void))
{
	press[button] = f;
}

void buttons__set_release_event(uint8_t button, void (*f)(void))
{
	release[button] = f;
}

void buttons__set_hold_event(uint8_t button, void (*f)(void))
{
	hold[button] = f;
}

