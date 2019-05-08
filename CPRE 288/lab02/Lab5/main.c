#include "lcd.h"
#include "timer.h"
#include "button.h"
#include <string.h>

/*
 * main.c
 */
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
		sendTheMessage();
	}

	data = (char) (UART1_DR_R & 0xFF);

	return data;
}
void sendTheMessage(void){

			button_checkButtons();
			char str[100];
			int i = 0;
			static int state = 0;
			if((GPIO_PORTE_DATA_R & 0b00100000) == 0b00000000){
				if(state == 0){
					sprintf(str, "Yes");
					sendAString(str);
					state = 1;
				}


			}
			else if((GPIO_PORTE_DATA_R & 0b00010000) == 0b00000000){
				if(state == 0){
					sprintf(str,"No");
					sendAString(str);
					state = 1;
				}

			}
			else if((GPIO_PORTE_DATA_R & 0b00001000) == 0b00000000){
				if(state == 0){
					sprintf(str, "Blue, no green, Ahhhhh!!");
					sendAString(str);
					state = 1;
				}
			}
			else if((GPIO_PORTE_DATA_R & 0b00000100) == 0b00000000){
				if(state == 0){
					sprintf(str, "Beam me up scotty\0");
					sendAString(str);
					state = 1;
				}

			}
			else if((GPIO_PORTE_DATA_R & 0b00000010) == 0b00000000){
				if(state == 0){
					sprintf(str, "I don't know");
					sendAString(str);
					state = 1;
				}
			}
			else if((GPIO_PORTE_DATA_R & 0b00000001) == 0b00000000){
				if(state == 0){
					sprintf(str, "May the force be with you!");
					sendAString(str);
					state = 1;
				}

			}
			else{
				state = 0;
			}

			memset(str, 0, sizeof(str));
			timer_waitMillis(100);

}
void WiFi_start(void) {
	GPIO_PORTB_DEN_R |= 0x00000004;
	GPIO_PORTB_DIR_R |= 0x00000004;
	GPIO_PORTB_DATA_R |= 0x00000004;//Enter command mode
	uart_sendChar(0x00); //Send command
	sendAString("password"); //Send WiFi PSK
	uart_sendChar(0); //NULL terminator
	char response = uart_receive(); //Wait for response
	GPIO_PORTB_DATA_R &= 0x1111111B; //Leave command mode
	if(response != 0) {
		//An error occurred…
	}
}
void sendAString(char str[]){
	int i = 0;
	for(i = 0; i < strlen(str); i++){
		uart_sendChar(str[i]);
	}
	uart_sendChar('\r');
	uart_sendChar('\n');
}

void main(void) {
	char data = 0;
	char str[20] = "";
	uart_init();
	lcd_init();
	button_init();
   	WiFi_start();

	while(1){
		int i = 0;
		while(strlen(str) < 20){
			    data = uart_receive();
				if(data != '\r'){
					uart_sendChar(data);
					str[i] = data;
					i++;
					lcd_printf("%c : %d", data, i);

				}
				else{
					uart_sendChar(data);
					uart_sendChar('\n');
					break;
				}


		}
		lcd_clear();
		lcd_printf("%s", str);
		memset(str, 0, sizeof(str));



	}

}
