/*
 * FAN.c
 *
 * Created: 8/11/2024 12:28:55 PM
 *  Author: Galal Abdelhamid
 */ 

#include <stdio.h>
#include <avr/io.h>

#include "UART.h"

#include "FAN.h"

void FAN_init()
{
	DDRB |= (1<<PB1) | (1<<PB2);	// set output pins to DC motor H-bridge
	PORTB |= (1<<PB1);		// set o/p to HIGH
	PORTB &= ~(1<<PB2);		// set o/p to LOW
}

char buff[64];
void FAN_set_speed(double temp)
{
	uint8_t duty_cycle;
	uint8_t speed_percentage;
	
	if (temp < 25)
	{
		duty_cycle = 0;
		speed_percentage = 0;
	}
	else if (temp <= 125)
	{
		duty_cycle = (uint8_t)((temp - 25) * 255 / 100);
		speed_percentage = temp - 25;
	}
	else
	{
		duty_cycle = 255;
		speed_percentage = 100;
	}
	
	sprintf(buff, "Fan speed: %u%% | ", speed_percentage);
	UART_SendString(buff);
	
	OCR0 = duty_cycle;
}
