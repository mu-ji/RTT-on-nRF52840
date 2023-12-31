/**
\brief SCuM-specific definition of the "leds" bsp module.

\author Tengfei Chang <tengfei.chang@inria.fr>, August 2016.
*/

#include "memory_map.h"
#include "stdint.h"
#include "leds.h"

//=========================== defines =========================================

//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================

void leds_init(void) {
    GPIO_REG__OUTPUT    &= ~0xF000;    // GPIO_REG__OUTPUT = 0bxxxx00000000, all LEDs off
}

// 0 <H17>
void    leds_error_on(void) {
    GPIO_REG__OUTPUT    |=  0x1000;
}
void    leds_error_off(void) {
    GPIO_REG__OUTPUT    &= ~0x1000;
}
void    leds_error_toggle(void) {
    GPIO_REG__OUTPUT    ^=  0x1000;
}
uint8_t leds_error_isOn(void) {
    return (uint8_t)(GPIO_REG__OUTPUT & 0x1000)>>12;
}

// 1 <K15>
void    leds_radio_on(void) {
    GPIO_REG__OUTPUT    |=  0x2000;
}
void    leds_radio_off(void) {
    GPIO_REG__OUTPUT    &= ~0x2000;
}
void    leds_radio_toggle(void) {
    GPIO_REG__OUTPUT    ^=  0x2000;
}
uint8_t leds_radio_isOn(void) {
    return (uint8_t)(GPIO_REG__OUTPUT & 0x2000)>>13;
}

// 2 <J13>
void    leds_sync_on(void) {
    GPIO_REG__OUTPUT    |=  0x4000;
}
void    leds_sync_off(void) {
    GPIO_REG__OUTPUT    &= ~0x4000;
}
void    leds_sync_toggle(void) {
    GPIO_REG__OUTPUT    ^=  0x4000;
}
uint8_t leds_sync_isOn(void) {
    return (uint8_t)(GPIO_REG__OUTPUT & 0x4000)>>14;
}

// 3 <N14>
void    leds_debug_on(void) {
    GPIO_REG__OUTPUT    |=  0x8000;
}
void    leds_debug_off(void) {
    GPIO_REG__OUTPUT    &= ~0x8000;
}
void    leds_debug_toggle(void) {
    GPIO_REG__OUTPUT    ^=  0x8000;
}
uint8_t leds_debug_isOn(void) {
    return (uint8_t)(GPIO_REG__OUTPUT & 0x8000)>>15;
}

void leds_all_on(void) {
    GPIO_REG__OUTPUT    |=  0xF000;
}
void leds_all_off(void) {
    GPIO_REG__OUTPUT    &= ~0xF000;
}
void leds_all_toggle(void) {
    GPIO_REG__OUTPUT    ^=  0xF000;
}

void leds_error_blink(void) {
    uint8_t i;
    volatile uint16_t delay;
    // turn all LEDs off
    GPIO_REG__OUTPUT    &= ~0xF000;
     
    // blink error LED for ~10s
    for (i=0;i<80;i++) {
        GPIO_REG__OUTPUT    ^=  0x8000;
        for (delay=0xffff;delay>0;delay--);
    }
}

void leds_circular_shift(void) {
    uint16_t temp_leds;
    if ((GPIO_REG__OUTPUT & 0xF000)==0) {         // if no LEDs on, switch on first one
        GPIO_REG__OUTPUT    |= 0x1000;
        return;
    }
    temp_leds = GPIO_REG__OUTPUT & 0xF000;        // retrieve current status of LEDs
    temp_leds <<= 1;                            // shift by one position
    if ((temp_leds & 0x1000)!=0) {
        temp_leds++;                            // handle overflow
    }
    GPIO_REG__OUTPUT    |= temp_leds;              // switch on the leds marked '1' in temp_leds
    GPIO_REG__OUTPUT    &= ~(~temp_leds & 0xF000);   // switch off the leds marked '0' in temp_leds
}

void leds_increment(void) {
   uint16_t led_counter;
   led_counter           = ((GPIO_REG__OUTPUT & 0xF000)+0x1000);
   GPIO_REG__OUTPUT     &= ~0xF000;                   //all LEDs off
   GPIO_REG__OUTPUT     |=  led_counter & 0xF000;     //LEDs on again
}

//=========================== private =========================================
