/*
 * servo.h
 *
 * Created: 2026-03-18 14:39:21
 *  Author: danie
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>


void servo_init(void);

void servo_set_us(uint16_t us);

void servo_neutral(void);

void servo_fire(void);




#endif /* SERVO_H_ */