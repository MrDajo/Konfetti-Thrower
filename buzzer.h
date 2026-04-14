/*
 * buzzer.h
 *
 * Created: 2026-03-18 14:39:54
 *  Author: danie
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include <stdint.h>

void buzzer_init(void);

void buzzer_tone(uint16_t freq_hz);

void buzzer_off (void);


void buzzer_beep(void);

void buzzer_tick(void);

void buzzer_armed_jingle(void);

void buzzer_fire_alarm(void);

void buzzer_safe_jingle(void);






#endif /* BUZZER_H_ */