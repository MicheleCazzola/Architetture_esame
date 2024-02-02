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

extern int result;
extern int cnt;

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

extern int pressure;
extern int byte_printed;
extern int result;

void TIMER0_IRQHandler (void)
{
	
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
	// Stop showing result
	if(byte_printed == 3){
		disable_timer(3);
		reset_timer(3);
		
		// Reset parameters
		byte_printed = 0;
		pressure = 0;
		
		// Reset timer 1
		reset_timer(0);
		
		// Switch led off
		LED_Out(0);
	}
	else{
		LED_Out(result & 0xFF);
		result = result >> 8;
		byte_printed++;
	}
	
	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

