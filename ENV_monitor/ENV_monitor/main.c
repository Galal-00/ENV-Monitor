/*
 * main.c
 *
 * Created: 11/8/2024
 * Author : Galal Abdelhamid
 */ 

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "TIMER.h"
#include "FAN.h"
#include "SHT21.h"

char buff[64];

ISR(TIMER1_COMPA_vect)
{
	cli();
	/* This interrupt should trigger every 100 msec */
	static uint8_t timer1_comp_count = 0;
	
	double temp = SHT21_get_temp();
	sprintf(buff, "Temperature: %ld°C | ", (int32_t)temp);
	UART_SendString(buff);
	FAN_set_speed(temp);
	
	if (timer1_comp_count % 2 == 0)
	{
		double RH = SHT21_get_RH();
		sprintf(buff, "Humidity: %ld%%", (int32_t)RH);
		UART_SendString(buff);
	}
	
	UART_SendString("\n\r");
	
	timer1_comp_count++;
	
	sei();
}

int main(void)
{
	/* Initialize peripherals */
    UART_Init();
	FAN_init();
	SHT21_init();
	TIMER_init();
	
	/* Enable Interrupts */
	sei();
	
    while (1){}
}