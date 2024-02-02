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
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
#define N 5

volatile int down_key1=0;

unsigned char VETT[N];
int val_int = 0;
unsigned char VAL;
int n = 0;

extern unsigned char get_and_sort(unsigned char* VETT, unsigned char VAL, int n);


void RIT_IRQHandler (void)
{	

	/* KEY 1 */
	if(down_key1!=0){
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){  /*KEY1*/
			reset_RIT();
			down_key1++;
			switch(down_key1){
				case 2:   
				
				disable_timer(1);
				val_int = LPC_TIM1 -> TC;
				enable_timer(1);
				
				// val_int -> 32 bit
				// 23 - 16 -> 8 bit -> VAL
				
				// 31			24-23			16- 15			10 8-7	5		0		
				// 0000000283212250000000 00000000 00000000
				VAL = (val_int & 0x00ff0000) >> 16;
				VETT[n] = VAL;
				n++;
				get_and_sort(VETT, VAL, n);
				if (n < N){
					LED_Out_Resersed(n);
				}
				else {
					enable_timer(0);
				}
				break;
				default:
					break;
			}
	}
	else {	/* button released */
		down_key1=0;			
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}	
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}
	
  return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
