#ifndef __LIGHTSENS_H__
#define __LIGHTSENS_H__

#include <stdint.h>

void lightsens__init(void);
void lightsens__update(void);
uint8_t lightsens__get_brightness(void);

#endif

