#include "time.h"
#include "config.h"

#include <stdbool.h>
#include <stdint.h>

static struct time time;
static uint8_t cycle_count;

static void advance_time(void);
static uint8_t get_days_of_month(uint8_t month, uint8_t year);
static bool is_leap_year(uint8_t year);

void time__init(void)
{
	/* set these to valid values */
	time.day_of_week = 6;
	time.day_of_month = 1;
	time.month = 1;
}

void time__update(void)
{
	cycle_count++;
	if (cycle_count >= 100)
	{
		advance_time();
		cycle_count = 0;
	}
}

void time__set_time(struct time t)
{
	time = t;
	cycle_count = 0;
}

struct time time__get_time(void)
{
	return time;
}

static void advance_time(void)
{
	time.second++;
	if (time.second < 60)
	{
		return;
	}
	time.second = 0;
	time.minute++;
	if (time.minute < 60)
	{
		return;
	}
	time.minute = 0;
	time.hour++;
	if (time.hour < 24)
	{
		return;
	}
	time.hour = 0;
	time.day_of_week++;
	if (time.day_of_week > 7)
	{
		time.day_of_week = 1;
	}
	time.day_of_month++;
	if (time.day_of_month <= get_days_of_month(time.month, time.year))
	{
		return;
	}
	time.day_of_month = 1;
	time.month++;
	if (time.month <= 12)
	{
		return;
	}
	time.month = 1;
	time.year++;
}

static uint8_t get_days_of_month(uint8_t month, uint8_t year)
{
	static uint8_t md[] = {29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (month == 2 && is_leap_year(year))
	{
		month = 0;
	}

	return md[month];
}

static bool is_leap_year(uint8_t year)
{
	/* As the year is a two-digit number from 0-99 (with an implicit offset
	 * of 2000), years after 2099 are undefined. It is therefore safe to
	 * simplify the detection of the leap year (the year 2100 is not a leap
	 * year even though it is divisible by 4). */
	return year % 4 == 0;
}

