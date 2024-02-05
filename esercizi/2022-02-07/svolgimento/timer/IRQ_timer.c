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
extern char PS, PN, PI;
extern unsigned char led_show;
int count;

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
	LED_Out(0);
	
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
	if(led_show == 1){
		LED_Out(0x80);
		enable_timer(2);
	}
	else if(led_show == 3){
		LED_Out(0x40);
		enable_timer(2);
	}
	else if(led_show == 5){
		LED_Out(0x20);
		enable_timer(2);
	}
	else if(led_show == 7){
		LED_Out(0);
	}
	
	led_show = (led_show + 1) % 7;
	count = 0;
	reset_timer(1);
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


void TIMER2_IRQHandler (void)
{
	count++;
	if(count == 20){
		count = 0;
		++led_show;
	}
	
	if(led_show == 2){
		if(led_value == 0x80){
			LED_Out(0);
		}
		else{
			LED_Out(0x80);
		}
	}
	else if(led_show == 3){
		LED_Out(PS);
		reset_timer(2);
		enable_timer(1);
	}
	else if(led_show == 4){
		if(led_value == 0x40){
			LED_Out(0);
		}
		else{
			LED_Out(0x40);
		}
	}
	else if(led_show == 5){
		LED_Out(PN);
		reset_timer(2);
		enable_timer(1);
	}
	else if(led_show == 6){
		if(led_value == 0x20){
			LED_Out(0);
		}
		else{
			LED_Out(0x20);
		}
	}
	else if(led_show == 7){
		LED_Out(PI);
		reset_timer(2);
		enable_timer(1);
	}
	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

