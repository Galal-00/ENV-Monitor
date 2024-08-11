/*
 * TWI.c
 *
 * Created: 8/11/2024 12:39:01 PM
 *  Author: Galal Abdelhamid
 */ 

#include <avr/io.h>
#include "TWI.h"

void TWI_init()
{
	TWSR = 0x00;
	TWBR = TWI_BITRATE();	// Set bit rate
}

void TWI_start()
{
	// Send start CONDn.
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	
	// Wait until transmission ends
	while (!(TWCR & (1<<TWINT)));
}

uint8_t TWI_write(uint8_t data)
{
	// Load data into TWDR
	TWDR = data;
	
	// Start transmission
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	// Wait until transmission ends
	while (!(TWCR & (1<<TWINT)));
	
	// Return the status bits
	return (TWSR & 0xF8);
}

uint8_t TWI_read_ACK()
{
	// Start receiving with ACK
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	
	// Wait until received
	while (!(TWCR & (1<<TWINT)));
	
	// Return received data
	return TWDR;
}

uint8_t TWI_read_NACK()
{
	// Start receiving with NACK
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	// Wait until received
	while (!(TWCR & (1<<TWINT)));
	
	// Return received data
	return TWDR;
}

void TWI_stop()
{
	// Send stop CONDn.
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}
