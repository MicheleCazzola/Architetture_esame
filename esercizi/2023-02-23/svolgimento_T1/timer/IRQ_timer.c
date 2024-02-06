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

extern char result;
extern char VAR;
volatile int tim_cnt;

void TIMER0_IRQHandler (void)
{
	if(led_value < 0xFF){
		LED_Out((led_value << 1) | 0x1);
	}
	else{
		reset_timer(0);
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
	// Reset
	enable_button(KEY1_PIN, EINT1_IRQn);
	enable_button(KEY2_PIN, EINT2_IRQn);
	VAR = 0;
	LED_Out(0);
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


void TIMER2_IRQHandler (void)
{
	if(++tim_cnt < 20){
		if(led_value == 0){
			LED_Out(result);
		}
		else{
			LED_Out(0);
		}
	}
	else{
		
		// Reset
		reset_timer(2);
		enable_button(KEY1_PIN, EINT1_IRQn);
		enable_button(KEY2_PIN, EINT2_IRQn);
		VAR = 0;
		LED_Out(0);
	}
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

