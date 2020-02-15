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

#include "buzzer.h"
#include "config.h"

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>

static uint8_t cycle_count;
static bool active;

void buzzer__init(void)
{
    DDR(BUZZER_PORT) |= (1 << BUZZER_PIN);
}

void buzzer__update(void)
{
    if (active)
    {
        if (cycle_count < 5)
        {
            PORT(BUZZER_PORT) |= (1 << BUZZER_PIN);
        }
        else
        {
            PORT(BUZZER_PORT) &= ~(1 << BUZZER_PIN);
        }

        cycle_count++;
        if (cycle_count >= 100)
        {
            cycle_count = 0;
        }
    }
}

void buzzer__activate(void)
{
    active = true;
    cycle_count = 0;
}

void buzzer__deactivate(void)
{
    active = false;
}   
