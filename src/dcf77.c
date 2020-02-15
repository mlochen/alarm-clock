#include "dcf77.h"
#include "config.h"
#include "time.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#define BIT(x) ((data[(x) / 8] & (1 << ((x) % 8))) ? 1 : 0)

static uint8_t data[8];
static uint8_t bit_count;

static void process_data(void);
static uint8_t check_even_parity(uint8_t i);

void dcf77__init(void)
{
	DDR(DCF77_PORT) &= ~(1 << DCF77_PIN);
}

void dcf77__update(void)
{
	static uint16_t cycle_counter;
	static uint8_t state_prev;

	cycle_counter++;
	uint8_t state_now = PIN(DCF77_PORT) & (1 << DCF77_PIN);

	if (state_now != state_prev)
	{
		if (state_now == 0 && cycle_counter > 6 && cycle_counter < 14)
		{
			/* logical 0 */
			data[bit_count / 8] &= ~(1 << (bit_count % 8));
			bit_count++;
		}
		if (state_now == 0 && cycle_counter > 16 && cycle_counter < 24)
		{
			/* logical 1 */
			data[bit_count / 8] |= (1 << (bit_count % 8));
			bit_count++;
		}
		if (state_now != 0 && cycle_counter > 100)
		{
			/* start of a new minute */
			process_data();
			bit_count = 0;
		}

		cycle_counter = 0;
		state_prev = state_now;
	}
}

static void process_data(void)
{
	static struct time time;

	bool valid = true;

	if (bit_count != 59)
	{
		valid = false;
	}
	if (BIT(0) == 1)
	{
		valid = false;
	}
	if (BIT(17) == 0 && BIT(18) == 1)
	{
		time.tz = MEZ;
	}
	else if (BIT(17) == 1 && BIT(18) == 0)
	{
		time.tz = MESZ;
	}
	else
	{
		valid = false;
	}
	if (BIT(20) != 1)
	{
		valid = false;
	}
	
	uint8_t temp;
	
	temp = data[2] >> 5;
	temp |= data[3] << 3;
	if (check_even_parity(temp))
	{
		time.minute = (temp & 0x0F) + ((temp >> 4) & 0x07) * 10;
	}

	temp = data[3] >> 5;
	temp |= data[4] << 3;
	temp &= 0x7F;
	if (check_even_parity(temp))
	{
		time.hour = (temp & 0x0F) + ((temp >> 4) & 0x03) * 10;
	}

	temp = data[4] >> 4;
	temp |= data[5] << 4;
	temp &= 0x3F;
	time.day_of_month = (temp & 0x0F) + (temp >> 4) * 10;

	temp = data[5] >> 2;
	temp &= 0x03;
	time.day_of_week = temp;

	temp = data[5] >> 5;
	temp |= data[6] << 3;
	temp &= 0x1F;
	time.month = (temp & 0x0F) + (temp >> 4) * 10;

	temp = data[6] >> 2;
	temp |= data[7] << 6;
	time.year = (temp & 0x0F) + (temp >> 4) * 10;
	
	if (valid)
	{
		time__set_time(time);
	}
}


static uint8_t check_even_parity(uint8_t i)
{
	i ^= i >> 4u;
	i ^= i >> 2u;
	i ^= i >> 1u;
	return (~i) & 1u;
}

