#include "button.h"
#include "lpc17xx.h"

#include <stdlib.h>
#include "../led/led.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"

#define MIN 20
#define MAX 80

// Control flags
extern int down_int0;
extern int down_key1;
extern int down_key2;	

volatile unsigned char VAR;
unsigned char vett[100];
unsigned int count;
unsigned int result;
unsigned char led_shift;

extern unsigned int totale_pressioni_con_filtro(unsigned char VETT[], unsigned int numero_misure, unsigned char max, unsigned char min);


void INT0_function(void){
	
	disable_button(KEY1_PIN, EINT1_IRQn);
	
	result = totale_pressioni_con_filtro(vett, count, MAX, MIN);
	
	// LED
	led_shift = 24;
	LED_Out((result >> led_shift) & 0xFF);
	enable_timer(1);
}

void KEY1_function(void){
	
}

void KEY2_function(void){
	// Spegnimento LED accesi da KEY1 e reset timer 0
	reset_timer(0);
	LED_Out(0);
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


