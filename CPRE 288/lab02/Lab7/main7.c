#include "timer.h"
#include "lcd.h"
#include "driverlib/interrupt.h"
volatile enum {LOW, HIGH, DONE} state;
volatile unsigned rising_time;
volatile unsigned falling_time;
/*
 * main.c
 */
void TIMER3B_Handler(void){
	TIMER3_ICR_R |= TIMER_ICR_CBECINT;
	//int event_time =
	//rising_time = 24;
	if(state == LOW /*GPIO_PORTB_DATA_R & 0x00000008 == 0x00000008*/){
		rising_time =  TIMER3_TBR_R;
		state = HIGH;

	}
	else if(state == HIGH /*GPIO_PORTB_DATA_R | 0x11111117 == 0x11111117*/){
			falling_time =  TIMER3_TBR_R;
			state = DONE;

	}
	//Blah
}
void timer_init(void){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	GPIO_PORTB_DEN_R |= 0x00000008;
	GPIO_PORTB_AFSEL_R |= 0x00000008;
	GPIO_PORTB_PCTL_R |= 0x00007000;


	SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;
	//en timer
	//TIMER3_CTL_R &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);
	TIMER3_CTL_R &= ~TIMER_CTL_TBEN;
	TIMER3_CTL_R |= 0x00000400;
	TIMER3_CFG_R |= 0x00000004;
	TIMER3_TBMR_R|= 0x00000017;
	TIMER3_TBILR_R |= 0x0000FFFF;
	TIMER3_IMR_R |= 0x00000400;
	TIMER3_CTL_R |= TIMER_CTL_TBEN;
	NVIC_EN1_R |= 0x10;z
}
void sendthePulse(void){
	// enabling clock
	//TIMER3_CTL_R |= TIMER_CTL_TBEN;

	GPIO_PORTB_AFSEL_R &= 0xFFFFFFF7;
	GPIO_PORTB_DIR_R |= 0x00000008;
	GPIO_PORTB_DATA_R |= 0x00000008;

	timer_waitMicros(5);


	GPIO_PORTB_DATA_R &= 0xFFFFFFF7;
	GPIO_PORTB_DIR_R &= 0xFFFFFFF7;
	GPIO_PORTB_AFSEL_R |= 0x00000008;


}
unsigned ping_read(){

	sendthePulse();
	double width = 0;
	while (state != DONE);
	TIMER3_CTL_R &= ~TIMER_CTL_TBEN;
	width = (falling_time - rising_time);
	if(falling_time - rising_time < 0){
			width += pow(2,16) - 1;
	}
	float sec = width/16000000;
	float distance = sec * 34000;
	distance = (falling_time - rising_time) * .0010625;
	distance = distance - 13;
	sec = sec * 1000;
	lcd_printf("width: %f\n sec: %f\n distance: %f",width, sec, distance);
	timer_waitMillis(500);



}

int main(void) {
	timer_init();
	IntRegister(INT_TIMER3B, TIMER3B_Handler);
	IntMasterEnable();
	lcd_init();
	while(1){
		ping_read();
		state = LOW;
		TIMER3_CTL_R |= TIMER_CTL_TBEN;

	}
	return 0;
}
