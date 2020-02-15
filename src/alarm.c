#include "alarm.h"
#include "buttons.h"
#include "buzzer.h"
#include "time.h"

static struct alarm alarm;

static void dec(void);
static void inc(void);
static void toggle(void);
static void edit(void);

void alarm__init(void)
{
	/* map callback functions to buttons */
	buttons__set_press_event(0, dec);
	buttons__set_hold_event(0, dec);
	buttons__set_press_event(1, inc);
	buttons__set_hold_event(1, inc);
	buttons__set_release_event(2, toggle);
	buttons__set_hold_event(2, edit);
}

void alarm__update(void)
{
	struct time time = time__get_time();

	if (alarm.enabled &&
		!alarm.active &&
		alarm.state == EDIT_OFF &&
		alarm.hour == time.hour &&
		alarm.minute == time.minute)
	{
		buzzer__activate();
		alarm.active = true;
	}

	if (!alarm.enabled && alarm.active)
	{
		buzzer__deactivate();
		alarm.active = false;
	}
}

struct alarm alarm__get_alarm_data(void)
{
	return alarm;
}

static void dec(void)
{
	if (alarm.state == EDIT_HOURS)
	{
		alarm.hour--;
		if (alarm.hour > 23)
		{
			alarm.hour = 23;
		}
	}
	else if (alarm.state == EDIT_MINUTES)
	{
		alarm.minute--;
		if (alarm.minute > 59)
		{
			alarm.minute = 59;
		}
	}
}

static void inc(void)
{
	if (alarm.state == EDIT_HOURS)
	{
		alarm.hour++;
		if (alarm.hour > 23)
		{
			alarm.hour = 0;
		}
	}
	else if (alarm.state == EDIT_MINUTES)
	{
		alarm.minute++;
		if (alarm.minute > 59)
		{
			alarm.minute = 0;
		}
	}
}

static void toggle(void)
{
	if (alarm.state == EDIT_OFF)
	{
		alarm.enabled = !alarm.enabled;
	}
	else if (alarm.state == EDIT_HOURS)
	{
		alarm.state = EDIT_MINUTES;
	}
	else if (alarm.state == EDIT_MINUTES)
	{
		alarm.state = EDIT_OFF;
	}
}

static void edit(void)
{
	if (alarm.state == EDIT_OFF)
	{
		alarm.state = EDIT_HOURS;
	}
}

