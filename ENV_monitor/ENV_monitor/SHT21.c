/*
 * SHT21.c
 *
 * Created: 8/11/2024 12:39:54 PM
 *  Author: Galal Abdelhamid
 */
 
#define F_CPU 8000000

#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

#include "TWI.h"

#include "SHT21.h"



void SHT21_init()
{
	TWI_init();
	_delay_ms(15);
}

double SHT21_get_temp()
{
	uint16_t temp_signal = 0;
	double temp = 0;
	
	TWI_start();
	
	TWI_write(SLAVE_W);
	
	TWI_write(SHT21_T_NO_HOLD_CMD);
	
	_delay_ms(85);
	
	TWI_start();
	
	// Poll until ACK is received
	while(TWI_write(SLAVE_R) != 0x40)
	{
		TWI_start();
	}
	
	temp_signal = TWI_read_ACK() << 8;
	
	temp_signal |= TWI_read_NACK();
	
	TWI_stop();
	
	temp_signal &= ~((1 << 0) | (1 << 1)); // set status bits to 0
	
	// Convert temperature signal to temperature value ( Celsius )
	temp = -46.85 + (175.72 * (double)temp_signal / 65536);
	
	return temp;
}

double SHT21_get_RH()
{
	uint16_t RH_signal = 0;
	double RH = 0;
	TWI_start();
	
	TWI_write(SLAVE_W);
	
	TWI_write(SHT21_H_NO_HOLD_CMD);
	
	_delay_ms(30);
	
	TWI_start();
	
	// Poll until ACK is received
	while(TWI_write(SLAVE_R) != 0x40)
	{
		TWI_start();
	}
	
	RH_signal = TWI_read_ACK() << 8;
	
	RH_signal |= TWI_read_NACK();
	
	TWI_stop();
	
	RH_signal &= ~((1 << 0) | (1 << 1)); // set status bits to 0
	
	// Convert relative humidity signal to relative humidity value
	RH = -6 + (125 * (double)RH_signal / 65536);
	
	return RH;
}