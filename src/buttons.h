#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <stdint.h>

void buttons__init(void);
void buttons__update(void);
void buttons__set_press_event(uint8_t button, void (*f)(void));
void buttons__set_release_event(uint8_t button, void (*f)(void));
void buttons__set_hold_event(uint8_t button, void (*f)(void));

#endif

