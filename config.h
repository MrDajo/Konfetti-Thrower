/*
 * config.h
 *
 * Created: 2026-03-18 14:38:37
 *  Author: danie
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 16000000UL

/*Pinnar*/

#define SWITCH_DDR DDRD

#define SWITCH_PORT PORTD

#define SWITCH_PIN_R PIND

#define SWITCH_PIN PD2


#define RADAR_DDR DDRD

#define RADAR_PIN_R PIND

#define RADAR_PIN PD3


#define LED_DDR DDRD

#define LED_PORT PORTD

#define LED_PIN PD4


#define SERVO_DDR DDRB

#define SERVO_PIN PB1


#define BUZZER_DDR DDRD

#define BUZZER_PORT PORTD

#define BUZZER_PIN PD6


#define SERVO_NEUTRAL_US 1500u

#define SERVO_FIRE_US 2200u


#define ARMING_DELAY_MS 10000u

#define COLDOWN_MS 5000u

#define SERVO_FIRE_MS 600u

#define SERVO_RESET_MS 500u

#define DEBOUNCE_MS 50u


#define TONE_BEEP 1000u

#define TONE_CONFIRM 800u

#define TONE_ARMED 2000u

#define TONE_ALARM 3000u

#define TONE_SAFE 500u

#endif /* CONFIG_H_ */