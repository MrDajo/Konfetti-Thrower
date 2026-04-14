/*
 * Test_mina_3.1.c
 *
 * Created: 2026-03-18 14:37:39
 * Author : danie
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "config.h"
#include "timer.h"
#include "servo.h"
#include "buzzer.h"


typedef enum{
    
    STATE_SAFE,
    STATE_ARMING,
    STATE_ARMED,
    STATE_FIRING,
    STATE_COOLDOWN
    
}State;


static void gpio_init(void){
    
    SWITCH_DDR &=~(1<<SWITCH_PIN);
    SWITCH_PORT |= (1<<SWITCH_PIN);
    
    
    RADAR_DDR &=~(1<< RADAR_PIN);
    
    LED_DDR |= (1<<LED_PIN);

}

static inline bool switch_pressed(void){
    
    return !(SWITCH_PIN_R & (1<<SWITCH_PIN));
}

static inline bool radar_detected (void){
    
    return (RADAR_PIN_R & (1<<RADAR_PIN));
    
}

static inline void led_on(void){
    
    LED_PORT |= (1<<LED_PIN);
}

static inline void led_off (void){
    
    LED_PORT &=~(1<< LED_PIN);
}

static void led_blink (uint8_t times, uint16_t period_ms){
    
    for (uint8_t i = 0; i < times; i++)
    {
        
        led_on();
        wait_ms(period_ms/2);
        led_off();
        wait_ms(period_ms/2);
        
    }
    
}

static void wait_for_switch_release(void){
    
    wait_ms(DEBOUNCE_MS);
    while(switch_pressed());
    wait_ms(DEBOUNCE_MS);
    
}

static State  handle_safe(void){
    
    servo_neutral();
    led_off();
    buzzer_safe_jingle();
    
    while (!switch_pressed()){
        led_blink(1,1000);
    }
    wait_for_switch_release();
    
    return STATE_ARMING;
    
}

static State handle_arming(void){
    
    uint32_t start = get_ms();
    uint32_t last_tick = start;
    
    while ((get_ms() - start)< ARMING_DELAY_MS){
        
        if (switch_pressed()){
            wait_for_switch_release();
            return STATE_SAFE;
        }
        
        if ((get_ms()-last_tick)>= 1000){
            
            buzzer_tick();
            last_tick = get_ms();
        }
        
        led_blink(1,200);
        
        
    }
    
    buzzer_armed_jingle();
    led_on();
    return STATE_ARMED;
}


static State handle_armed(void){
    
    led_on();
    
    while (true)
    {
        if (switch_pressed())
        {
            wait_for_switch_release();
            return STATE_SAFE;
        }
        if (radar_detected())
        {
            return STATE_FIRING;
        }
    }
}


static State handle_firing(void){
    
    buzzer_fire_alarm();
    
    servo_fire();
    wait_ms(SERVO_FIRE_MS);
    
    return STATE_COOLDOWN;
    
}


static State handle_cooldown(void){
    
    servo_neutral();
    wait_ms(SERVO_RESET_MS);
    
    uint32_t start = get_ms();
    while ((get_ms()-start)<COLDOWN_MS)
    {
        
        if (switch_pressed())
        {
            wait_for_switch_release();
            return STATE_SAFE;
        }
        led_blink(1,500);
    }
    
    return STATE_ARMED;
}


int main(void){
    
    gpio_init();
    timer2_init();
    servo_init();
    buzzer_init();
    sei();
    
    State state = STATE_SAFE;
    
    
    
    
    while (1)
    {
        
        switch (state){
            
            case STATE_SAFE:
            state = handle_safe();
            
            break;
            
            case STATE_ARMING :
            state = handle_arming();
            
            break;
            
            case STATE_ARMED:
            state= handle_armed();
            
            break;
            
            case STATE_FIRING:
            state = handle_firing();
            
            break;
            
            case STATE_COOLDOWN:
            state = handle_cooldown();
            
            
            
        }
        
    }
}

