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
