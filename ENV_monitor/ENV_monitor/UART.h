/*
 * UART.h
 *
 * Created: 11/8/2024
 * Author : Galal Abdelhamid
 */ 

#include <avr/io.h>

#ifndef UART_H_
#define UART_H_

#define BAUD 9600
#define F_CPU_UART 8000000UL
#define BAUD_PRESCALE ((F_CPU_UART/16/BAUD) - 1)

void UART_Init();

void UART_TxChar(char ch);

char UART_RxChar();

void UART_SendString(char *str);

#endif /* UART_H_ */