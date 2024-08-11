/*
 * TIMER.c
 *
 * Created: 8/11/2024 12:34:11 PM
 *  Author: Galal Abdelhamid
 */

#include <avr/io.h>
#include "TIMER.h"

void TIMER_init()
{
	PWM_init();
	TIMER1_init();
};

void PWM_init()
{
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);	//Fast PWM, 8-bit, non-inverted, no prescaling
	DDRB |= (1<<PB3);	//Set pin OC0 as output
}

void TIMER1_init()
{
	/* CTC mode, 100 msec period */
	TCNT1 = 0;							// start counter at 0
	TCCR1A = 0x00;						// OC1A & OC1B disconnected, CTC mode
	TCCR1B |= (1<<WGM12) | (1<<CS12);	// CTC mode, /256 prescaling
	OCR1A = 3125 - 1;					// 3125 ticks to clear the counter
	TIMSK |= (1 << OCIE1A);				// Enable interrupt on compare match
}
