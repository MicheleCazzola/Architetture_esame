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
volatile unsigned int VAR1 = 0, VAR2 = 0;
volatile unsigned int vett[N];
volatile unsigned int count = 0;
volatile char mode = 0;

extern unsigned int calcola_somma_prodotto(unsigned int VETT[], unsigned int n, char *alarm);

void viewMode(){
	char alarm;
	unsigned int result;
	
	result = calcola_somma_prodotto(vett, count, &alarm);
	
	mode = 1;
	reset_timer(0);
	reset_timer(1);
	
	if(alarm == 0xFF){
		LED_Out(result);
	}
	else{
		LED_Out(0xFF);
		enable_timer(2);
	}
}

void RIT_IRQHandler (void)
{		
	// Stop RIT eventuale: evitare pending interrupt del rit
	disable_RIT();
	reset_RIT();
	
	// Polling joystick standard (select + 4 direzioni ortogonali)
	//joystick_controller();
	
	// Polling joystick avanzato (select + 8 direzioni)
	joystick_controller_advanced();
	
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
			pressure += 50;
				switch(down_key1){
					case 2: KEY1_function(); break;
					default: break;
				}
			}
		else {	/* button released */
			down_key1=0;
			
			if(mode == 0){
				
				reset_timer(0);
				if(0 < pressure && pressure < 2000){
					VAR1 += 2;
					
					if(VAR1 <= 0xF){
						LED_Out_custom(VAR1 << 4, 4, 4);
					}
					else{
						LED_Out_custom(0xF0, 4, 4);
						enable_timer(0);
					}
				}
				else if(0 < pressure && pressure < 3000){
					VAR1 += 3;
					
					if(VAR1 <= 0xF){
						LED_Out_custom(VAR1 << 4, 4, 4);
					}
					else{
						LED_Out_custom(0xF0, 4, 4);
						enable_timer(0);
					}
				}
				else if(pressure > 0){
					viewMode();
				}
			}
			
			pressure = 0;
			
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
	
	// Abilitazione RIT eventuale
	enable_RIT();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
