/*
 * servo.c
 *
 * Created: 2026-03-18 14:41:20
 *  Author: danie
 */ 
#include <avr/io.h>
#include "servo.h"
#include "config.h"


void servo_init(void){
    SERVO_DDR |=(1<<SERVO_PIN);
    
    
    
    TCCR1A = (1<<COM1A1) | (1<<WGM11);
    TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11)| (1<<CS10);
    
    ICR1 = 4999;
    
    servo_neutral();
    
}

void servo_set_us(uint16_t us){
    OCR1A= us/4;
}

void servo_neutral(void){
    
    servo_set_us(SERVO_NEUTRAL_US);
}

void servo_fire(void){
    servo_set_us(SERVO_FIRE_US);
}