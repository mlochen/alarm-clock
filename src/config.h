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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define F_CPU 16000000

/* IO configuration */

#define DDR_(port)      DDR##port
#define PIN_(port)      PIN##port
#define PORT_(port)     PORT##port

#define DDR(port)       DDR_(port)
#define PIN(port)       PIN_(port)
#define PORT(port)      PORT_(port)

/* dcf77 signal input */
#define DCF77_PORT      C
#define DCF77_PIN       0

/* display */
#define RS_PORT         B
#define RS_PIN          0
#define RW_PORT         B
#define RW_PIN          1
#define E_PORT          B
#define E_PIN           2
#define DATA_PORT       D

/* light sensor */
/* must be an ADC PIN */
#define LIGHTSENS_ADC   5

/* backlight */
/* this can not be changed as the backlight is controlled by fast PWM of
 * timer 2 connected to the OC2 pin */
#define BACKLIGHT_PORT  B
#define BACKLIGHT_PIN   3

/* buzzer */
#define BUZZER_PORT     C
#define BUZZER_PIN      4

/* buttons */
#define BUTTON1_PORT    C
#define BUTTON1_PIN     1
#define BUTTON2_PORT    C
#define BUTTON2_PIN     2
#define BUTTON3_PORT    C
#define BUTTON3_PIN     3

#endif
