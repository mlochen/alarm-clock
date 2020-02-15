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

#include "lightsens.h"
#include "config.h"

#include <avr/io.h>

void lightsens__init(void)
{
    /* initialize the ADC */
    ADMUX = (1 << ADLAR) | LIGHTSENS_ADC;
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADFR) |
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

void lightsens__update(void)
{
    ;
}

uint8_t lightsens__get_brightness(void)
{
    return ADCH;
}
