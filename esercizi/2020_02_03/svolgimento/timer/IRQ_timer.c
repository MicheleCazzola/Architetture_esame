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

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern unsigned char led_value;					/* defined in funct_led								*/

extern int pos;
extern int count;

extern unsigned char v[N];

void TIMER0_IRQHandler (void)
{
	if(pos < N){
		unsigned char elem = v[pos];
		LED_Out(elem);
		pos++;
	}
	// Fine vettore
	else if(pos == N){
		
		// Stop timer
		disable_timer(0);
		
		// Reset count
		count = 0;
		
		LED_Out(0);
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
	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

