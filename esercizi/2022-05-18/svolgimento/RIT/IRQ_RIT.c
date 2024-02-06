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

volatile int pressure = 0;
extern unsigned char VAR;
extern unsigned char vett[100];
extern unsigned int count;

void RIT_IRQHandler (void)
{		
	// Stop RIT eventuale: evitare pending interrupt del rit
	disable_RIT();
	reset_RIT();
	
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
			
			// Riabilitazione INT0 solo se non si è invocato assembly
			if(down_int0 < 2){
				enable_button(INT0_PIN, EINT0_IRQn);
			}
			
			down_int0=0;
			
		}
	}
	
	// KEY1
	if(down_key1 > 0){
		down_key1++;
		if((LPC_GPIO2->FIOPIN & (1<<KEY1_PIN)) == 0){
			
			// Pressione consecutiva in ms
				pressure += 50;
			
				switch(down_key1){
					case 2: KEY1_function(); break;
					default: break;
				}
			}
		else {	/* button released */
			down_key1=0;
			
			// Rumore
			if(pressure == 0){
				enable_button(KEY1_PIN, EINT1_IRQn);
			}
			// Store VAR
			else if(pressure > 100 * 0xFF){
				VAR = 0xFF;
				
				// Visualizzazione con LED lampeggianti
				LED_Out(VAR);
				enable_timer(0);
			}
			else{
				VAR = pressure/100;
				
				LED_Out(VAR);
			}
			
			pressure = 0;
			
			// Abilitazione KEY2
			enable_button(KEY2_PIN, EINT2_IRQn);
		}
	}
	
	// KEY2
	if(down_key2 > 0){
		down_key2++;
		if((LPC_GPIO2->FIOPIN & (1<<KEY2_PIN)) == 0){
			
			// Calcolo pressione
			pressure += 50;
				switch(down_key2){
					case 2: KEY2_function(); break;
					default: break;
				}
			}
		else {	/* button released */
			down_key2=0;
			
			// Caso di rumore
			if(pressure == 0){
				enable_button(KEY2_PIN, EINT2_IRQn);
			}
			// Pressione minore 1 secondo, non rumore
			else if(pressure < 1000){
				vett[count++] = VAR;
			}
			// Pressione superiore
			else {
				count = 0;
			}
			
			// Vettore saturo -> Assembly
			if(count == 100){
				INT0_function();
			}
			else{
				// Abilitazione INT0 e riabilitazione KEY1 solo se non si invoca assembly
				enable_button(INT0_PIN, EINT0_IRQn);
				enable_button(KEY1_PIN, EINT1_IRQn);
			}
			
			// Reset pressione
			pressure = 0;
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
