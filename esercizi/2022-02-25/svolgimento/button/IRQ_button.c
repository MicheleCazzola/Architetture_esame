#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../GLCD/GLCD.h"

// Control flags
extern int down_int0;
extern int down_key1;
extern int down_key2;	

extern int count;
extern char vett_input[100];
char vett_output[100];
int RES;

extern int traduzione_morse(char* vett_input, char* vett_output);

void translate(){
	
	// Abilitazione key2 e int0
	enable_button(INT0_PIN, EINT0_IRQn);
	enable_button(KEY2_PIN, EINT2_IRQn);
	
	// Traduzione
	RES = traduzione_morse(vett_input, vett_output);
	
	// Risultato mostrato per 2 secondi
	LED_Out(RES);
	enable_timer(1);
}

void INT0_function(void){
	
}

void KEY1_function(void){
	
	// Termine frase
	vett_input[count++] = 4;
	LED_Out(0xFF);
	
	// Traduzione a fine timer, dopo 3 secondi
	enable_timer(2);
}

void KEY2_function(void){
	
	// Reset
	count = 0;
	disable_button(INT0_PIN, EINT0_IRQn);
	disable_button(KEY2_PIN, EINT2_IRQn);
	LCD_Clear(White);
	LED_Out(0);
}
	
void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	down_int0 = 1;
	disable_button(INT0_PIN, EINT0_IRQn);
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	down_key1 = 1;
	disable_button(KEY1_PIN, EINT1_IRQn);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	down_key2 = 1;
	disable_button(KEY2_PIN, EINT2_IRQn);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


