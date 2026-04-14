/*
 * timer.c
 *
 * Created: 2026-03-18 14:41:32
 *  Author: danie
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

static volatile uint32_t ms_ticks = 0;

ISR(TIMER2_COMPA_vect){
    ms_ticks++;
}

void timer2_init(void){
    
    TCCR2A = (1<<WGM21);
    
    TCCR2B = (1<<CS22)|(1<<CS20);
    
    OCR2A = 124;
    
    TIMSK2 = (1<<OCIE2A);
    
}

uint32_t get_ms(void){
    uint32_t t;
    cli();
    t=ms_ticks;
    sei();
    return t;
}

void wait_ms(uint32_t duration){
    
    uint32_t start = get_ms();
    while ((get_ms()-start)< duration);
    
}