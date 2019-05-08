/*
 * uart.h
 *
 *  Created on: Mar 23, 2017
 *      Author: lmandrew
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>

void uart_init(void);
void uart_sendChar(char data);
char uart_receive(void);
void sendAString(uint8_t* str, uint8_t len);



#endif /* UART_H_ */
