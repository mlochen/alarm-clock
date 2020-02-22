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

#include "dcf77.h"
#include "config.h"
#include "time.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

#define BIT(x) ((data[(x) / 8] & (1 << ((x) % 8))) ? 1 : 0)

static uint8_t data[8];
static uint8_t bit_count;
static struct time time_buffer[3];
static uint8_t time_index;
static uint32_t invalid_period;

static void process_data(void);
static uint8_t check_even_parity(uint8_t i);
static void check_time_buffer(void);
static bool compare_time(struct time * time1, struct time * time2);

void dcf77__init(void)
{
    DDR(DCF77_PORT) &= ~(1 << DCF77_PIN);
    invalid_period = UINT32_MAX;
}

void dcf77__update(void)
{
    static uint16_t cycle_counter;
    static uint8_t state_prev;

    cycle_counter++;
    uint8_t state_now = PIN(DCF77_PORT) & (1 << DCF77_PIN);

    if (state_now != state_prev)
    {
        if (state_now == 0 && bit_count < 64 &&
            cycle_counter > 6 && cycle_counter < 14)
        {
            /* logical 0 */
            data[bit_count / 8] &= ~(1 << (bit_count % 8));
            bit_count++;
        }
        if (state_now == 0 && bit_count < 64 &&
            cycle_counter > 16 && cycle_counter < 24)
        {
            /* logical 1 */
            data[bit_count / 8] |= (1 << (bit_count % 8));
            bit_count++;
        }
        if (state_now != 0 && cycle_counter > 100)
        {
            /* start of a new minute */
            process_data();
            bit_count = 0;
        }

        cycle_counter = 0;
        state_prev = state_now;
    }

    if (invalid_period < UINT32_MAX)
    {
        invalid_period++;
    }
}

uint32_t dcf77__get_invalid_period(void)
{
    return invalid_period;
}

static void process_data(void)
{
    static struct time time;

    bool valid = true;

    if (bit_count != 59)
    {
        valid = false;
    }
    if (BIT(0) == 1)
    {
        valid = false;
    }
    if (BIT(17) == 0 && BIT(18) == 1)
    {
        time.tz = MEZ;
    }
    else if (BIT(17) == 1 && BIT(18) == 0)
    {
        time.tz = MESZ;
    }
    else
    {
        valid = false;
    }
    if (BIT(20) != 1)
    {
        valid = false;
    }
    
    uint8_t minute;
    minute = data[2] >> 5;
    minute |= data[3] << 3;
    if (!check_even_parity(minute))
    {
        valid = false;
    }
    minute = (minute & 0x0F) + ((minute >> 4) & 0x07) * 10;
    if (minute < 60)
    {
        time.minute = minute;
    }
    else
    {
        valid = false;
    }

    uint8_t hour;
    hour = data[3] >> 5;
    hour |= data[4] << 3;
    hour &= 0x7F;
    if (!check_even_parity(hour))
    {
        valid = false;
    }
    hour = (hour & 0x0F) + ((hour >> 4) & 0x03) * 10;
    if (hour < 24)
    {
        time.hour = hour;
    }
    else
    {
        valid = false;
    }

    uint8_t day_of_month;
    day_of_month = data[4] >> 4;
    day_of_month |= data[5] << 4;
    day_of_month &= 0x3F;
    day_of_month = (day_of_month & 0x0F) + (day_of_month >> 4) * 10;
    if (day_of_month <= 31)
    {
        time.day_of_month = day_of_month;
    }
    else
    {
        valid = false;
    }

    uint8_t day_of_week;
    day_of_week = data[5] >> 2;
    day_of_week &= 0x07;
    if (day_of_week != 0)
    {
        time.day_of_week = day_of_week;
    }
    else
    {
        valid = false;
    }

    uint8_t month;
    month = data[5] >> 5;
    month |= data[6] << 3;
    month &= 0x1F;
    month = (month & 0x0F) + (month >> 4) * 10;
    if (month != 0 && month <= 12)
    {
        time.month = month;
    }
    else
    {
        valid = false;
    }

    uint8_t year;
    year = data[6] >> 2;
    year |= data[7] << 6;
    year = (year & 0x0F) + (year >> 4) * 10;
    if (year < 100)
    {
        time.year = year;
    }
    else
    {
        valid = false;
    }

    uint8_t date_data;
    date_data = data[4] & 0xF0;
    date_data ^= data[5];
    date_data ^= data[6];
    date_data ^= data[7] & 0x07;
    if (!check_even_parity(date_data))
    {
        valid = false;
    }
    
    if (valid)
    {
        time_buffer[time_index] = time;
        time_index = (time_index + 1) % 3;
        check_time_buffer();
    }
}


static uint8_t check_even_parity(uint8_t i)
{
    i ^= i >> 4u;
    i ^= i >> 2u;
    i ^= i >> 1u;
    return (~i) & 1u;
}

static void check_time_buffer(void)
{
    struct time * time1 = &time_buffer[time_index];
    struct time * time2 = &time_buffer[(time_index + 1) % 3];
    struct time * time3 = &time_buffer[(time_index + 2) % 3];
    bool comp1 = compare_time(time1, time2);
    bool comp2 = compare_time(time2, time3);
    if (comp1 && comp2)
    {
        time__set_time(*time3);
        invalid_period = 0;
    }
}

static bool compare_time(struct time * time1, struct time * time2)
{
    return time1->tz == time2->tz &&
           time1->minute + 1 == time2->minute &&
           time1->hour == time2->hour &&
           time1->day_of_month == time2->day_of_month &&
           time1->day_of_week == time2->day_of_week &&
           time1->month == time2->month &&
           time1->year == time2->year;
}
