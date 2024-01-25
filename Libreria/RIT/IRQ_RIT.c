/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;


void RIT_IRQHandler (void)
{			
	static uint8_t position=0;
	if(down_1!=0){  
			down_1 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){

			switch(down_1){
			case 2:
				if( position == 7){
					LED_On(0);
					LED_Off(7);
					position = 0;
				}
				else{
					LED_Off(position);
					LED_On(++position);
				}
				break;
			default:
				if(down_1 % 10 == 0)
					{
						if( position == 7){
							LED_On(0);
							LED_Off(7);
							position = 0;
							}
						else{
							LED_Off(position);
							LED_On(++position);
						}
					}					
				break;
		}
	}
	else {	/* button released */
		down_1=0;			
		NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
	}
	if(down_2!=0){  
			down_2 ++;  
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			switch(down_2){
			case 2:
				if( position == 0){
					LED_On(7);
					LED_Off(0);
					position = 7;
				}
				else{
					LED_Off(position);
					LED_On(--position);
				}
				break;
			default:
				if(down_2 % 10 == 0)
					{
						if( position == 0){
							LED_On(7);
							LED_Off(0);
							position = 7;
							}
						else{
							LED_Off(position);
							LED_On(--position);
						}
					}					
			
				break;
		}
	}
	else {	/* button released */
		down_2=0;			
		NVIC_EnableIRQ(EINT2_IRQn); 							 /* enable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	}
	}
		
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
