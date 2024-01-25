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
int down_int0 = 0;
int down_key1 = 0;
int down_key2 = 0;

void RIT_IRQHandler (void)
{		
	// Stop RIT eventuale
	//disable_RIT();
	//reset_RIT();
	
	// Polling joystick standard (select + 4 direzioni ortogonali)
	joystick_controller();
	
	// Polling joystick avanzato (select + 8 direzioni)
	//joystick_controller_advanced();
	
	// INT0
	if(down_int0 > 0){
		down_int0++;
		if((LPC_GPIO2->FIOPIN & (1<<INT0_PIN)) == 0){
				switch(down_int0){
					case 2: INT0_function(); break;
					default: break;
				}
			}
		else {	/* button released */
			down_int0=0;
			enable_button(INT0_PIN, EINT0_IRQn);
		}
	}
	
	// KEY1
	if(down_key1 > 0){
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
	if(down_key2 > 0){
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
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
	// Abilitazione RIT eventuale
	//enable_RIT();
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
