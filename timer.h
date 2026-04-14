/*
 * timer.h
 *
 * Created: 2026-03-18 14:40:45
 *  Author: danie
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>

void timer2_init(void);

uint32_t get_ms(void);

void wait_ms (uint32_t duration);




#endif /* TIMER_H_ */