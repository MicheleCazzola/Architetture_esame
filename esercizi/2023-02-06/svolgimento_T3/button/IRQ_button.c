#include "button.h"
#include "lpc17xx.h"

#include <stdlib.h>
#include "../led/led.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"

// Control flags
extern int down_int0;
extern int down_key1;
extern int down_key2;	

extern int VETT[N];
extern int count;
extern int full;
volatile char mode;

extern int differenza_media_positivi_negativi(int V[], unsigned int num, char* over);

void INT0_function(void){
	
	int result, n;
	char over = 0;
	
	if(mode == 0){
		
		n = (full > 0) ? N : count;
		result = differenza_media_positivi_negativi(VETT, n, &over);
		
		// Stop blinking timer
		reset_timer(0);
		LED_Out(0);
		
		if(over == 0){
			if(result >= 0){
				LED_Out(0xFF);
			}
			else{
				LED_Out(0x80);
			}
		}
		else{
			LED_Out(0xFF);
			enable_timer(1);
		}
		
		mode = 1;
	}
	else{
		
		// Boot
		reset_timer(1);
		count = 0;
		LED_Out(0);
		full = 0;
		mode = 0;
	}
	
	
}

void KEY1_function(void){

}

void KEY2_function(void){
	
}
	
void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	down_int0 = 1;
	disable_button(INT0_PIN, EINT0_IRQn);
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	down_key1 = 1;
	disable_button(KEY1_PIN, EINT1_IRQn);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	down_key2 = 1;
	disable_button(KEY2_PIN, EINT2_IRQn);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


