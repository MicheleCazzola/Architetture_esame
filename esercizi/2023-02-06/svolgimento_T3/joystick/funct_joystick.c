/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        High level joystick management functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"
#include "../button/button.h"
#include "../timer/timer.h"
#include "../led/led.h"

#define NO_MOVE -1

volatile int VETT[N];
volatile int count;
volatile int full;

// Conta numero di input del joystick selezionati
static int countPressed(){
	int i, r;
	for(i = r = 0; i < 5; i++){
		r += ((LPC_GPIO1->FIOPIN & (1 << (i + 25))) == 0);
	}
	
	return r;
}

// Funzione di controllo del joystick per scelta
void joystick_controller(){
	
	int i;
	
	// Vettore di contatori per ogni possibile direzione di input
	// Incrementato ogni volta che l'input corrispondente risulta premuto
	static int pressed[5] = {0, 0, 0, 0, 0};
	
	// Vettore di pin
	const int pins[5] = {
		25, 	// SELECT
		26, 	// DOWN
		27,		// LEFT
		28,		// RIGHT
		29		// UP
	};
	
	// Solo un input alla volta
	if(countPressed() > 1){
		return;
	}
	
	for(i = 0; i < 5; i++){
		// Joystick SELECT/DOWN/LEFT/RIGHT/UP premuto
		if((LPC_GPIO1->FIOPIN & (1 << pins[i])) == 0){
			pressed[i]++;
			if(pressed[i] == 1){
				switch(i){
					case 0: break;
					case 1: {
						
						// Inserimento in posizione e incremento circolare
						VETT[count] = LPC_TIM2->TC;
						count = (count + 1) % N;
						
						// Aggiornamento riempimenti
						if(count == 0){
							
							if(full < 4){
								LED_Out(full);
							}
							else{
								LED_Out(0x3);
								enable_timer(0);
							}
							
							full++;
						}
						
						break;
					}
					case 2: break;
					case 3: break;
					default /* case 4 */: break;
				}
			}
		}
		// Joystick SELECT/DOWN/LEFT/RIGHT/UP rilasciato
		else{
			pressed[i] = 0;
			
			switch(i){
					case 0: break;
					case 1: break;
					case 2: break;
					case 3: break;
					default /* case 4 */: break;
			}
		}
	}
}

// Funzione di controllo del joystick per spostamenti
void joystick_controller_advanced() {
	
	// Mosse possibili
	const int moves[5][2] = {
		{NO_MOVE, NO_MOVE}, 	// SELECT
		{0, 1},								// DOWN
		{-1, 0},							// LEFT
		{1, 0},								// RIGHT
		{0, -1}								// UP
	};
	
	// Vettore di contatori per ogni possibile direzione di input
	// Incrementato ogni volta che l'input corrispondente risulta premuto
	static int pressed[5] = {0, 0, 0, 0, 0};
	static int cmdToExecute = 0;
	
	int i, h, v, sel;
	
	h = v = sel = 0;
	for(i = 0; i <= 4; i++){
		
		// Joystick SELECT/DOWN/LEFT/RIGHT/UP premuto
		if((LPC_GPIO1->FIOPIN & (1 << (i + 25))) == 0){
			pressed[i]++;
			
			// Se prima pressione, calcolo incrementi h/v
			if(pressed[i] == 1){
				
				cmdToExecute = 1;
				if(i == 0){
					sel = 1;
				}
				else{
					h += moves[i][0];
					v += moves[i][1];
				}
			}
		}
		// Joystick SELECT/DOWN/LEFT/RIGHT/UP rilasciato
		else{
				pressed[i]=0;
		}
	}
	
	// Se almeno un comando è premuto, si svolgono le funzioni del joystick
	if(cmdToExecute){
		
		// Azzeramento flag comando da eseguire
		cmdToExecute = 0;
		
		// SELECT
		if(sel){}
		// MOVE
		else{
			// LEFT-UP
			if(h == -1 && v == -1){}
			// LEFT
			if(h == -1 && v == 0){}
			// LEFT-DOWN
			if(h == -1 && v == 1){}
			// UP
			if(h == 0 && v == -1){}
			// DOWN
			if(h == 0 && v == 1){}
			// RIGHT-UP
			if(h == 1 && v == -1){}
			// RIGHT
			if(h == 1 && v == 0){}
			// RIGHT-DOWN
			if(h == 1 && v == 1){}
		}
	}
	
}
