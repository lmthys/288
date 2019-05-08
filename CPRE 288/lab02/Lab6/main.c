/*
 * main.c
 */
#include "timer.h"
#include "lcd.h"
#include <math.h>

void adc_init(){

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

	SYSCTL_RCGCADC_R |= 0x1;

	GPIO_PORTB_AFSEL_R |= 0x01;

	GPIO_PORTB_DEN_R &= 0b11111110;

	GPIO_PORTB_AMSEL_R |= 0x01;

	GPIO_PORTB_ADCCTL_R = 0x00;

	ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

	ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;

	ADC0_SSMUX0_R |= 0x000A;

	ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);

	ADC0_SAC_R |= 0x00000004;

	ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;


}
unsigned ADC_read(char channel){
	//disable ADC0SS0 sample sequencer to configure it
	ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
	//set 1st sample to use the channel ADC pin
	ADC0_SSMUX0_R |= channel;
	//re-enable ADC0 SS0
	ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
	//initiate SS0 conversion
	ADC0_PSSI_R=ADC_PSSI_SS0;
	//wait for ADC conversion to be complete
	while((ADC0_RIS_R & ADC_RIS_INR0) == 0){}
	//clear interrupt
	ADC0_ISC_R=ADC_ISC_IN0;
	return ADC0_SSFIFO0_R;
}

int main(void) {
	lcd_init();
	adc_init();
	//ADC_read(0);
	//initiate SS1 conversion
	while(1){
		ADC0_PSSI_R=ADC_PSSI_SS0;
		//wait for ADC conversion to be complete
		while((ADC0_RIS_R & ADC_RIS_INR0) == 0){
		//wait
		}
		//grab result
		double value = ADC0_SSFIFO0_R;
		double y = value/25918;
		y = log(y);
		y = y / (-0.957);
		y = exp(y);
// This is the first part :)



		timer_waitMillis(50);
		lcd_clear();
		lcd_printf("Q Value:%.1f\n y:%.1f cm", value, y);
	}
}
