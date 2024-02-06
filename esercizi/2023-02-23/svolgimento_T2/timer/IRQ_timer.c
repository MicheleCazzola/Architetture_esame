/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"
#include "../button/button.h"

extern unsigned char led_value;					/* defined in funct_led								*/
extern unsigned short int vett[N];
extern unsigned short int VAR;
extern int count;

extern unsigned int concat_sum(unsigned short int VETT[], unsigned int dim, char* alarm);

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	if(led_value == 0xFF){
		LED_Out(0);
	}
	else{
		LED_Out(0xFF);
	}
	
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


void TIMER2_IRQHandler (void)
{
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	unsigned int result;
	char alarm = 0;
	
	// Reset LEDs
	reset_timer(0);
	LED_Out(0);
	
	// Insert new element
	if(count < N){
		vett[count++] = VAR;
		VAR = 0;
	}
	
	result = concat_sum(vett, count, &alarm);
	
	// Show result
	if(alarm == 0){
		LED_Out_reverse((result & 0x00000FF0) >> 4);
	}
	else{
		LED_Out(0xFF);
		enable_timer(0);
	}
	
	// Saturazione
	if(count == N){
		count = 0;
	}
	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

