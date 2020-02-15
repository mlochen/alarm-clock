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

#include "displayif.h"
#include "config.h"

#include "alarm.h"
#include "backlight.h"
#include "display.h"
#include "lightsens.h"
#include "time.h"

#include <util/delay.h>

static void print_number(uint8_t n);
static void print_day_of_week(uint8_t dow);

void displayif__init(void)
{
    /* wait for the display controller */
    _delay_ms(100);

    display__display_clear();
    display__set_function(0x18);
    display__display_on_off(0x04);
}

void displayif__update(void)
{
    static uint8_t flash_count;

    struct time time = time__get_time();

    /* print the time */
    display__set_DDRAM_address(0x00);
    display__display_clear();
    print_number(time.hour);
    display__write_data(':');
    print_number(time.minute);
    display__write_data(':');
    print_number(time.second);

    /* print the date */
    display__set_DDRAM_address(0x40);
    print_day_of_week(time.day_of_week);
    display__write_data(' ');
    print_number(time.day_of_month);
    display__write_data('.');
    print_number(time.month);
    display__write_data('.');
    print_number(time.year);

    struct alarm alarm = alarm__get_alarm_data();

    /* print alarm data */
    display__set_DDRAM_address(0x0A);
    if (alarm.enabled)
    {
        display__write_data('*');
    }
    else
    {
        display__write_data(' ');
    }
    if (alarm.state == EDIT_HOURS && flash_count > 24)
    {
        display__write_data(' ');
        display__write_data(' ');
    }
    else
    {
        print_number(alarm.hour);
    }
    display__write_data(':');
    if (alarm.state == EDIT_MINUTES && flash_count > 24)
    {
        display__write_data(' ');
        display__write_data(' ');
    }
    else
    {
        print_number(alarm.minute);
    }

    /* brightness */
    uint8_t b = lightsens__get_brightness();
    display__set_DDRAM_address(0x4C);
    display__write_data('0' + ((b / 100) % 10));
    display__write_data('0' + ((b / 10) % 10));
    display__write_data('0' + (b % 10));
    backlight__set_brightness(b);


    flash_count++;
    if (flash_count > 49)
    {
        flash_count = 0;
    }
}

static void print_number(uint8_t n)
{
    display__write_data('0' + ((n / 10) % 10));
    display__write_data('0' + (n % 10));
}

static void print_day_of_week(uint8_t dow)
{
    char * s = "  ";

    switch(dow)
    {
        case(1): s = "Mo"; break;
        case(2): s = "Di"; break;
        case(3): s = "Mi"; break;
        case(4): s = "Do"; break;
        case(5): s = "Fr"; break;
        case(6): s = "Sa"; break;
        case(7): s = "So"; break;
    }

    display__write_data(s[0]);
    display__write_data(s[1]);
}
