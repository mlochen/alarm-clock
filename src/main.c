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

#include "alarm.h"
#include "backlight.h"
#include "buttons.h"
#include "buzzer.h"
#include "dcf77.h"
#include "display.h"
#include "displayif.h"
#include "lightsens.h"
#include "time.h"

#include <avr/interrupt.h>
#include <avr/io.h>

/* every 10ms */
ISR(TIMER1_COMPA_vect)
{
    alarm__update();
    backlight__update();
    buttons__update();
    buzzer__update();
    dcf77__update();
    display__update();
    displayif__update();
    lightsens__update();
    time__update();
}

int main()
{
    alarm__init();
    backlight__init();
    buttons__init();
    buzzer__init();
    dcf77__init();
    display__init();
    displayif__init();
    lightsens__init();
    time__init();

    /* timer 1 initialization */
    TCCR1B |= (1 << CS12) | (1 << WGM12);
    OCR1A = 624;
    TIMSK |= (1 << OCIE1A);

    sei();
    while(1);
}
