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

#include "backlight.h"
#include "config.h"

#include <avr/io.h>

void backlight__init(void)
{
    DDR(BACKLIGHT_PORT) |= (1 << BACKLIGHT_PIN);

    /* initialize timer 2 */
    TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS22);
}

void backlight__update(void)
{
    ;
}

void backlight__set_brightness(uint8_t b)
{
    OCR2 = b;
}
