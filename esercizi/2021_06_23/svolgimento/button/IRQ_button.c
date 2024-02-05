#include "button.h"
#include "lpc17xx.h"

#include <stdlib.h>
#include "../led/led.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"

#define N 10

// Control flags
extern int down_int0;
extern int down_key1;
extern int down_key2;	

volatile unsigned int count;
volatile unsigned char VAR;
unsigned char vett[N];
volatile unsigned char finished;

extern unsigned int sopra_la_media(unsigned char VETT[], unsigned int n); 

void INT0_function(void){
	
	unsigned int above_avg;
	
	vett[count] = VAR;
	VAR = 0;
	count++;
	
	if(count == N || (count > 1 && vett[count-1] == vett[count-2])){
		finished = 1;
		above_avg = sopra_la_media(vett, count);
		
		if(above_avg <= 0xFF){
			LED_Out(above_avg);
		}
		else{
			LED_Out(0xAA);
			enable_timer(0);
		}
	}
	else{
		LED_Out(VAR);
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


