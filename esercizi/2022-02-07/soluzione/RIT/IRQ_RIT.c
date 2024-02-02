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


volatile int down_key1;
volatile int down_key2;
volatile int down_int0;

static int8_t OP_1 = 0;
static int8_t OP_2 = 0;
static uint8_t OPER = 0; // 1 -> sum, 2 -> sub
static int8_t RES = 0;


// The program implements a state machine
typedef enum {
	OP_1_ACQUISITION,
	OP_2_ACQUISITION,
	OPER_ACQUISITION,
	DONE
} STATE;

// Initial state
static STATE state = OP_1_ACQUISITION;

extern char execute_operation(char OP_1, char OP_2, unsigned char OPER, char* OVERFLOW);

void RIT_IRQHandler (void)
{					
	static int js_up=0;
	static int js_left=0;
	static int js_right=0;
	static int js_down=0;
	

	
 // START JOYSTICK **********************************************	
	
	
	// JOY down
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick down pressed */
		js_down++;
		if (js_down == 1){
			if (state == OP_1_ACQUISITION){
					if (OP_1 > -128){
						OP_1--;
						LED_Out(OP_1);
					}
			}
			else if (state == OP_2_ACQUISITION){
					if (OP_2 > -128)
					{
						OP_2--;
						LED_Out(OP_2);
					}
			}
		}
	}
	else{
			js_down=0;
	}
	
	
		// JOY left
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick left pressed */
		js_left++;
		if (js_left == 1){
			// CODE HERE
		}
	}
	else{
			js_left=0;
	}
	
	
		// JOY right
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick right pressed */
		js_right++;
		if (js_right ==1){
			 if (state == OP_1_ACQUISITION){
					state = OP_2_ACQUISITION;
					LED_Out(0);
			 }
			 else if (state == OP_2_ACQUISITION){
					state = OPER_ACQUISITION;
					LED_Out(0);
			 }
		}
	}
	else{
			js_right=0;
	}
	
	// JOY UP
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		js_up++;
		if (js_up == 1){
			if (state == OP_1_ACQUISITION){
				if (OP_1 < 0x7f){
					OP_1++;
					LED_Out(OP_1);
				}
			}
			else if (state == OP_2_ACQUISITION){
			if (OP_2 < 0x7f){
					OP_2++;
					LED_Out(OP_2);
				}			
			}		
		}
	}
	else{
			js_up=0;
	}
	
	 // END JOYSTICK **********************************************	
	
	// INT0
	if (down_int0!=0){
		if ((LPC_GPIO2->FIOPIN & (1 << 10)) == 0) { // pressed
			down_int0++;
			switch(down_int0){
				case 2:
					// YOUR CODE HERE
				if (state == OPER_ACQUISITION) {
					char OVERFLOW = 0;
					
		//			RES = execute_operation( OP_1,  OP_2, OPER, &OVERFLOW);
					
				}
				break;
				default:
					break;
			}
		}
		else{ // button released
			down_int0=0;
			NVIC_EnableIRQ(EINT0_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<20);
		}
	}
	
		// KEY1
	if (down_key1!=0){
		if ((LPC_GPIO2->FIOPIN & (1 << 11)) == 0) { // pressed
			down_key1++;
			switch(down_key1){
				case 2:
					// YOUR CODE HERE
				if (state == OPER_ACQUISITION) {
					// Sum selected
					OPER = 1;
					LED_Out(0xFF);
				}
				break;
				default:
					break;
			}
		}
		else{ // button released
			down_key1=0;
			NVIC_EnableIRQ(EINT1_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<22);
		}
	}
	
	
		// KEY2
	if (down_key2!=0){
		if ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0) { // pressed
			down_key2++;
			switch(down_key2){
				case 2:
					// YOUR CODE HERE
				if (state == OPER_ACQUISITION) {
					// Subtraction selected
					OPER = 2;
					LED_Out(0xFF);
				}
				break;
				default:
					break;
			}
		}
		else{ // button released
			down_key2=0;
			NVIC_EnableIRQ(EINT2_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<24);
		}
	}
	
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
