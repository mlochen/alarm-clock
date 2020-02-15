#ifndef __BACKLIGHT_H__
#define __BACKLIGHT_H__

#include <stdint.h>

void backlight__init(void);
void backlight__update(void);
void backlight__set_brightness(uint8_t b);

#endif

