#include "button.h"
#include "lpc17xx.h"

#include <stdlib.h>
#include "../led/led.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"

extern unsigned int VAR1;
extern unsigned int status;

// Control flags
extern int down_int0;
extern int down_key1;
extern int down_key2;	

void INT0_function(void){
	status = 2;
	
	VAR1 = VAR1/4;
}

// Get timer counter value
void KEY1_function(void){
	
	disable_timer(1);
	reset_timer(1);
	LED_Out(0);
	
	status = 1;
	
	VAR1 = VAR1 + LPC_TIM3->TC;
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


