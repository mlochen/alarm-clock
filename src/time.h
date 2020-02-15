/*
 * Copyright (C) 2020 Marco Lochen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
