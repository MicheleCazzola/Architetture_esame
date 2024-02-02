#include "button.h"
#include "lpc17xx.h"

#include <stdlib.h>
#include "../led/led.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"

extern int e1, e2;

// Control flags
extern int down_int0;
extern int down_key1;
extern int down_key2;	

volatile int timer2_counting = 0;

void INT0_function(void){
	
	// Reset timer causa reset contatori pressione
	e1 = e2 = 0;
	
	// Spegnimento LED
	LED_Out(0);
	
	if(timer2_counting == 0){
		
		timer2_counting = 1;
		enable_timer(2);
	}
	else{
		LPC_TIM2->TC = 0;
	}
}

void KEY1_function(void){
	e1++;
}

void KEY2_function(void){
	e2++;
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


