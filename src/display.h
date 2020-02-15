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

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>

void display__init(void);
void display__update(void);
void display__display_clear(void);
void display__return_home(void);
void display__entry_mode_set(uint8_t data);
void display__display_on_off(uint8_t data);
void display__shift(uint8_t data);
void display__set_function(uint8_t data);
void display__set_CGRAM_address(uint8_t data);
void display__set_DDRAM_address(uint8_t data);
uint8_t display__read_busy_flag_and_address(void);
void display__write_data(uint8_t data);

#endif
