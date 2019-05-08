#include "timer.h"
#include "lcd.h"
#include "driverlib/interrupt.h"
#include "button.h"
#include "uart.h"
#include "ir.h"
#include "WiFi.h"
#include "ping.h"

unsigned pulse_period = 320000;
float count = 0;
int swi;
float p = 0;
float ir = 0;
int oD = 0;
int counter = -1;
int fO = 0;
float aD[100];
int mid[100];
float lastCount = 0.0;

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

void collectData(void){



	char send[100];
	sprintf(send,"%f     %f     %f\n\r",count,p,ir);
	sendAString(send, strlen(send));
	move_servo(count);
	timer_waitMillis(100);
	ping_trigger();
	p = ping_getDistance();
	ir = ir_getDistance();
	if(count > 10){
		if(p < 129 && ir < 60){
			if(oD == 0){
				counter++; // counter is how many objects
				aD[counter] = count; // count is the angle the servo is at
				mid[counter] = count;
				lastCount = count;
				oD = 1; // detecting object
				fO = 0;
			}

		}
		else if(ir > 100){
					oD = 0; // done detecting
						if(fO == 0){
							aD[counter] = count - lastCount; // detecting the smaller object
							fO = 1;
						}
		}
	}
	//ir_getValue();



}
int main(void) {
	timer_init();
	button_init();
	pin_init();
	lcd_init();
	lcd_clear();
	ping_init();
	uart_init();
	ir_init();
	swi = 1;
	count = 0;

	char psk[] = "pass12345";

	//WiFi_start(psk);

	char first[100];
	sprintf(first, "Degrees     IR Distance (cm)     Sonar Distance(cm)\n\r");
	sendAString(first, strlen(first));

	while(count < 180){


//		if(count > 180){
//			count = 180;
//		}
//		if(count < 0){
//			count = 0;
//		}
//		while( count < 180){
			count = count + 2;
			collectData();

//		}


//		while( count > 0){
//			count = count - 2;
//			collectData();
//		}


	}
	sprintf(first, "Objects Found:%d\n\r", counter+1);
	sendAString(first, strlen(first));
	lcd_printf(first);
	float min = aD[0];
	int i = 0;
	int index = 0;
	for(i = 0; i < counter+1; i++){
		if(aD[i] < min){
			min = aD[i];
			index = i;
		}
	}
	lcd_printf("Objects:%d\nIndex:%d\nAngular Dis:%.2f\n",counter+1, index+1, min);
	float middle = (aD[index])/2;
	middle = middle + mid[index];
	move_servo(middle);

	return 0;
}
