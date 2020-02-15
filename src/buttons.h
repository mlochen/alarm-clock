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

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <stdint.h>

void buttons__init(void);
void buttons__update(void);
void buttons__set_press_event(uint8_t button, void (*f)(void));
void buttons__set_release_event(uint8_t button, void (*f)(void));
void buttons__set_hold_event(uint8_t button, void (*f)(void));

#endif
