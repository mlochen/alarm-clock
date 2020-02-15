#include "display.h"
#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

enum rs_state {
	INSTRUCTION = 0,
	DATA = 1
};

enum rw_state {
	WRITE = 0,
	READ = 1
};

enum e_state {
	OFF = 0,
	ON = 1
};

static void set_rs(enum rs_state state);
static void set_rw(enum rw_state state);
static void set_e(enum e_state state);
static void put(enum rs_state rs, uint8_t data);
static uint8_t get(void);
static void wait(void);

void display__init(void)
{
	DDR(RS_PORT) |= (1 << RS_PIN);
	DDR(RW_PORT) |= (1 << RW_PIN);
	DDR(E_PORT) |= (1 << E_PIN);
}

void display__update(void)
{
	;
}

void display__display_clear(void)
{
	wait();
	put(INSTRUCTION, 0x01);
}

void display__return_home(void)
{
	wait();
	put(INSTRUCTION, 0x02);
}

void display__entry_mode_set(uint8_t data)
{
	wait();
	put(INSTRUCTION, (0x04 | (0x03 & data)));
}

void display__display_on_off(uint8_t data)
{
	wait();
	put(INSTRUCTION, (0x08 | (0x07 & data)));
}

void display__shift(uint8_t data)
{
	wait();
	put(INSTRUCTION, (0x10 | (0x0F & data)));
}

void display__set_function(uint8_t data)
{
	wait();
	put(INSTRUCTION, (0x20 | (0x1F & data)));
}

void display__set_CGRAM_address(uint8_t data)
{
	wait();
	put(INSTRUCTION, (0x40 | (0x3F & data)));
}

void display__set_DDRAM_address(uint8_t data)
{
	wait();
	put(INSTRUCTION, (0x80 | (0x7F & data)));
}

uint8_t display__read_busy_flag_and_address(void)
{
	return get();
}

void display__write_data(uint8_t data)
{
	wait();
	put(DATA, data);
}

static void set_rs(enum rs_state state)
{
	if (state == DATA)
	{
		PORT(RS_PORT) |= (1 << RS_PIN);
	}
	else
	{
		PORT(RS_PORT) &= ~(1 << RS_PIN);
	}
}

static void set_rw(enum rw_state state)
{
	if (state == READ)
	{
		PORT(RW_PORT) |= (1 << RW_PIN);
	}
	else
	{
		PORT(RW_PORT) &= ~(1 << RW_PIN);
	}
}

static void set_e(enum e_state state)
{
	if (state == ON)
	{
		PORT(E_PORT) |= (1 << E_PIN);
	}
	else
	{
		PORT(E_PORT) &= ~(1 << E_PIN);
	}
}

static void put(enum rs_state rs, uint8_t data)
{
	DDR(DATA_PORT) = 0xFF;
	PORT(DATA_PORT) = data;

	set_rs(rs);
	set_rw(WRITE);

	set_e(ON);
	_delay_us(1);
	set_e(OFF);
}

static uint8_t get(void)
{
	DDR(DATA_PORT) = 0x00;

	set_rs(INSTRUCTION);
	set_rw(READ);

	set_e(ON);
	_delay_us(1);
	uint8_t data = PIN(DATA_PORT);
	set_e(OFF);

	return data;
}

static void wait(void)
{
	while(display__read_busy_flag_and_address() & 0x80);
}

