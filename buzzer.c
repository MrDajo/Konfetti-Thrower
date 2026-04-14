/*
 * buzzer.c
 *
 * Created: 2026-03-18 14:41:09
 *  Author: danie
 */ 
#include <avr/io.h>
#include "buzzer.h"
#include "config.h"
#include "timer.h"


static uint8_t freq_to_ocr(uint16_t freq_hz){
    
    uint32_t ocr = (F_CPU /(16UL*(uint32_t)freq_hz));
    
    if (ocr > 0) ocr -= 1;
    if (ocr > 255) ocr = 255;
    
    return (uint8_t)ocr;
}

void buzzer_init(void){
    
    BUZZER_DDR |=(1<<BUZZER_PIN);
    
    
    TCCR0A = (1<<COM0A0) | (1<<WGM01);
    
    TCCR0B = (1<<CS01);
    
    
    TIMSK0 = 0;
    
    buzzer_off();
    
}

void buzzer_tone(uint16_t freq_hz){
    OCR0A = freq_to_ocr(freq_hz);
    
    TCCR0A |= (1<< COM0A0);
}

void buzzer_off(void){
    TCCR0A &=  ~(1<<COM0A0);
    
    BUZZER_PORT &=~( 1<<BUZZER_PIN);
}


void buzzer_beep(void){
    buzzer_tone(TONE_BEEP);
    wait_ms(100);
    buzzer_off;
}

void buzzer_tick (void){
    
    buzzer_tone(TONE_CONFIRM);
    wait_ms(40);
    buzzer_off();
    
}

void buzzer_armed_jingle(void){
    
    buzzer_tone(800);
    wait_ms(120);
    buzzer_off();
    wait_ms(60);
    buzzer_tone(1200);
    wait_ms(120);
    buzzer_off();
    wait_ms(60);
    buzzer_tone(2000);
    wait_ms(200);
    buzzer_off();
    
    
}

void buzzer_fire_alarm(void){
    
    for (uint8_t i = 0; i < 3; i++)
    {
        buzzer_tone(TONE_ALARM);
        wait_ms(80);
        buzzer_off();
        wait_ms(60);
    }
}

void buzzer_safe_jingle(void){
    
    buzzer_tone(1500);
    wait_ms(150);
    buzzer_off();
    wait_ms(60);
    buzzer_tone(700);
    wait_ms(200);
    buzzer_off();
    
}