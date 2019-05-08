#include "timer.h"
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "button.h"
unsigned pulse_period = 320000;
int count;
int swi;

void timer_init(){


	SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;
	TIMER1_CTL_R &= 0xEFF;
	TIMER1_TBMR_R = 0xA;
	TIMER1_CFG_R = 0x4;
	TIMER1_TBILR_R = 0xE200;
	TIMER1_TBPR_R = 0x4;
	TIMER1_TBPMR_R = 0x4;
	TIMER1_TBMATCHR_R  = 0x8440;
	TIMER1_CTL_R = 0x100;
}
void move_servo(float degree){
	if(degree > 180){
		degree = 180;
	}
	if(degree < 0){
		degree = 0;
	}
	float deg = (28100);
	deg = deg * (degree/180);
	deg = deg + 8000;
	//converting degrees to pulse width
	unsigned pulse_width = deg;

	int stor = 0;
	//int stor1 = 0;
	stor = pulse_period - pulse_width;
	//stro1 = stor;
	TIMER1_TBPMR_R = stor >> 16;
	TIMER1_TBMATCHR_R = stor & 0xFFFF;


	// move to the position
	//GPIO_PORTB_DATA_R |= 0x00000020;



}
void pin_init(void){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	GPIO_PORTB_DEN_R |= 0x00000020;
	GPIO_PORTB_DIR_R |= 0x00000020;
	GPIO_PORTB_AFSEL_R |= 0x00000020;
	GPIO_PORTB_PCTL_R |= 0x00700000;

}
void buttons(void){

			button_checkButtons();

			int state = 0;
			if((GPIO_PORTE_DATA_R & 0b00100000) == 0b00000000){
				if(state == 0){
					if(swi == 1)
						count = count+1;
					else if(swi == -1)
						count--;
					state = 1;
				}


			}
			else if((GPIO_PORTE_DATA_R & 0b00010000) == 0b00000000){
				if(state == 0){
					if(swi == 1)
						count = count + 2.5;
					else if(swi == -1)
						count = count - 2.5;

					state = 1;
				}

			}
			else if((GPIO_PORTE_DATA_R & 0b00001000) == 0b00000000){
				if(state == 0){
					if(swi == 1)
						count = count + 5;
					else if(swi == -1)
						count = count - 5;
					state = 1;
				}
			}
			else if((GPIO_PORTE_DATA_R & 0b00000100) == 0b00000000){

					if(swi == -1)
						swi = 1;
					else if(swi == 1)
						swi = -1;



			}

			timer_waitMillis(100);

}
int main(void) {
	timer_init();
	button_init();
	pin_init();
	lcd_init();
	lcd_clear();
	swi = 1;
	count = 90;
	while(1){
		lcd_printf("Direction:%d\n Angle:%d", swi,count);
		buttons();
		if(count > 180){
			count = 180;
		}
		if(count < 0){
			count = 0;
		}
		move_servo(count);

	}
	return 0;
}
