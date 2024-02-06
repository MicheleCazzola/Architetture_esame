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

extern unsigned char led_value;					/* defined in funct_led								*/
extern int buffer[N];
extern unsigned int count;

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
	int value;
	
	disable_timer(3);
	value = LPC_TIM3->TC;
	enable_timer(3);
	
	LED_Out((value & 0x0000FF00) >> 8);
	
	if(count < N){
		buffer[count] = value;
		count++;
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

