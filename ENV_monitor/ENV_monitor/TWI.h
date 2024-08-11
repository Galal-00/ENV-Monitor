/*
 * TWI.h
 *
 * Created: 8/11/2024 11:57:21 AM
 *  Author: Galal Abdelhamid
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <math.h>

#define F_CPU_TWI			8000000UL
#define F_SCL_TWI			200000UL

#define TWI_BITRATE() ((F_CPU_TWI / F_SCL_TWI) - 16) / (2 * pow(4, (TWSR & ((1 << TWPS0) | (1<<TWPS1)))))

void TWI_init();

void TWI_start();

uint8_t TWI_write(uint8_t data);

uint8_t TWI_read_ACK();

uint8_t TWI_read_NACK();

void TWI_stop();

#endif /* TWI_H_ */