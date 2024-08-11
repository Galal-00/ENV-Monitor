/*
 * SHT21.h
 *
 * Created: 8/11/2024 11:58:27 AM
 *  Author: Galal Abdelhamid
 */ 


#ifndef SHT21_H_
#define SHT21_H_

#define SLAVE_ADDR			0b1000000
#define SLAVE_W				(SLAVE_ADDR << 1)
#define SLAVE_R				((SLAVE_ADDR << 1) | 1)

#define SHT21_T_HOLD_CMD		0xE3
#define SHT21_H_HOLD_CMD		0xE5
#define SHT21_T_NO_HOLD_CMD		0xF3
#define SHT21_H_NO_HOLD_CMD		0xF5
#define SHT21_SOFT_RESET		0xFE

void SHT21_init();

double SHT21_get_temp();

double SHT21_get_RH();

#endif /* SHT21_H_ */