#ifndef __ALARM_H__
#define __ALARM_H__

#include <stdint.h>
#include <stdbool.h>

struct alarm {
	uint8_t hour;
	uint8_t minute;
	bool enabled;
	bool active;
	enum {
		EDIT_OFF,
		EDIT_HOURS,
		EDIT_MINUTES
	} state;
};

void alarm__init(void);
void alarm__update(void);
struct alarm alarm__get_alarm_data(void);

#endif

