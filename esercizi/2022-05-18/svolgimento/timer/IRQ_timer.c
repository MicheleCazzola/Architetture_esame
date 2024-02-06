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
extern unsigned int result;
extern unsigned char led_shift;
extern unsigned int count;
extern unsigned char VAR;

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
	if(led_value == 0){
		LED_Out(0xFF);
	}
	else{
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
	if(led_shift > 0){
		led_shift -= 8;
		LED_Out((result >> led_shift) & 0xFF);
	}
	else{
		reset_timer(1);
		
		// Boot
		count = 0;
		VAR = 0;
		LED_Out(0);
		enable_button(KEY1_PIN, EINT1_IRQn);
	}
	
	
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

