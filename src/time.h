#ifndef __TIME_H__
#define __TIME_H__

#include <stdint.h>

enum timezone {
	MEZ,
	MESZ
};

struct time {
	enum timezone tz;
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day_of_month;
	uint8_t day_of_week;
	uint8_t month;
	uint8_t year;
};

void time__init(void);
void time__update(void);
void time__set_time(struct time t);
struct time time__get_time(void);

#endif

