#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>

void display__init(void);
void display__update(void);
void display__display_clear(void);
void display__return_home(void);
void display__entry_mode_set(uint8_t data);
void display__display_on_off(uint8_t data);
void display__shift(uint8_t data);
void display__set_function(uint8_t data);
void display__set_CGRAM_address(uint8_t data);
void display__set_DDRAM_address(uint8_t data);
uint8_t display__read_busy_flag_and_address(void);
void display__write_data(uint8_t data);

#endif

