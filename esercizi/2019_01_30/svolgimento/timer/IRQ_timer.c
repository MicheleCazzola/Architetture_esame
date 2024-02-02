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

extern unsigned int count_bits_to_1(unsigned int VAR1);

extern unsigned char led_value;					/* defined in funct_led								*/
extern unsigned int status;
extern unsigned int result;
extern unsigned int VAR1;

void TIMER0_IRQHandler (void)
{
	int val;
	result = count_bits_to_1(VAR1);
	val = 11 - result;
	
	status = 5;
	
	if(result <= 3){
		LED_Out(0);
	}
	else if(4 <= result && result <= 11){
		LED_On(val);
	}
	else{
		LED_Out(0xFF);
		enable_timer(1);
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
	if(status == 5){
		if(led_value == 0){
			LED_Out(0xFF);
		}
		else{
			LED_Out(0);
		}
		
		VAR1 = 9;
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

