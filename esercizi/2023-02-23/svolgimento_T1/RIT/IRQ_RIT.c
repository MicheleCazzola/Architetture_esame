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
#include "../button/button.h"
#include "../joystick/joystick.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

// Variabili di controllo dei pulsanti
// Incrementate ad ogni RIT handler, se avviene
// immediatamente in seguito alla pressione del
// pulsante corrispondente
volatile int down_int0 = 0;
volatile int down_key1 = 0;
volatile int down_key2 = 0;

volatile char VAR;
volatile unsigned int pressure = 0;
volatile char result;
extern int tim_cnt;

extern char fibonacci(char var);

void RIT_IRQHandler (void)
{		
	// Stop RIT eventuale: evitare pending interrupt del rit
	disable_RIT();
	reset_RIT();
	
	// Entrambi
	if(down_key1 > 0 && down_key2 > 0){
		++down_key1;
		++down_key2;
		if((LPC_GPIO2->FIOPIN & (1<<KEY1_PIN)) == 0 && (LPC_GPIO2->FIOPIN & (1<<KEY2_PIN)) == 0){
				pressure += 50;
			}
		else {	
			
			if(pressure > 500){
				
				result = fibonacci(VAR);
				
				// LED
				if((char)result == (char)0xFF){
					LED_Out(0);
					enable_timer(0);
				}
				else{
					LED_Out(result);
					tim_cnt = 0;
					enable_timer(2);
				}
			}
			else{
				enable_button(KEY1_PIN, EINT1_IRQn);
				enable_button(KEY2_PIN, EINT2_IRQn);
			}
			
			
			down_key1 = down_key2 = 0;
			pressure = 0;
		}
		
		
	}
	
	// KEY1
	else if(down_key1 > 0){
		down_key1++;
		if((LPC_GPIO2->FIOPIN & (1<<KEY1_PIN)) == 0){
				switch(down_key1){
					case 2: KEY1_function(); break;
					default: break;
				}
			}
		else {	/* button released */
			down_key1=0;
			enable_button(KEY1_PIN, EINT1_IRQn);
		}
	}
	
	// KEY2
	else if(down_key2 > 0){
		down_key2++;
		if((LPC_GPIO2->FIOPIN & (1<<KEY2_PIN)) == 0){
				switch(down_key2){
					case 2: KEY2_function(); break;
					default: break;
				}
			}
		else {	/* button released */
			down_key2=0;
			enable_button(KEY2_PIN, EINT2_IRQn);
		}
	}
	
	// Abilitazione RIT eventuale
	enable_RIT();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
