/*
 * uart.c
 *
 *  Created on: Mar 23, 2017
 *      Author: lmandrew
 */
#include "uart.h"
#include "lcd.h"
#include "timer.h"
#include "button.h"
#include <string.h>
void uart_init(void){

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;

	GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);

	GPIO_PORTB_PCTL_R |= 0x00000011;

	GPIO_PORTB_DEN_R |= (BIT0 | BIT1);

	GPIO_PORTB_DIR_R &= ~BIT0;

	GPIO_PORTB_DIR_R |= BIT1;

	uint16_t iBRD = 8;

	uint16_t fBRD = 44;

	UART1_CTL_R &= ~(UART_CTL_UARTEN);

	UART1_IBRD_R = iBRD;
	UART1_FBRD_R = fBRD;

	UART1_LCRH_R = UART_LCRH_WLEN_8;

	UART1_CC_R = UART_CC_CS_SYSCLK;

	UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);

}
void uart_sendChar(char data){

	while(UART1_FR_R & 0x20){

	}

	UART1_DR_R = data;
}
char uart_receive(void){
	char data = 0;

	while(UART1_FR_R & UART_FR_RXFE){

	}

	data = (char) (UART1_DR_R & 0xFF);

	return data;
}
void sendAString(uint8_t* str, uint8_t len){
	int i = 0;
	for(i = 0; i < len; i++){
		uart_sendChar(*(str+i));
	}
	//uart_sendChar('\r');
	//uart_sendChar('\n');
}



