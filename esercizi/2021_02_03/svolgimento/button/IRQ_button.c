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

extern int mode;
extern unsigned char valore_iniziale;
extern unsigned char numero_variazioni;

void INT0_function(void){
	
}

void KEY1_function(void){

}

void KEY2_function(void){
	mode = 1;
	valore_iniziale = 2;
	numero_variazioni = 0;
	reset_timer(0);
	LED_Out(0xFF);
	
	enable_timer(3);
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


