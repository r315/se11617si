/**
* @file		timer.c
* @brief	Contains API source code for controlling timer 0.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/
#include <timer.h>


void TIMER0_Init(unsigned int frequency){	

	TIMER0->TCR = TIMER_CR; // disable timer and reset
	TIMER0->PC = 0;			// reset prescale counter
	TIMER0->CTCR = 0; 		// Timer mode

	if(!frequency) frequency = 1;
	TIMER0->PR = (PCLK / frequency) - 1; // pr = pclk / frequency, pclk = cclk / vpdiv (default 4)
	
	TIMER0->TCR = TIMER_CE;	//start timer
}


unsigned int TIMER0_GetValue(void){
	return TIMER0->TC;
}

unsigned int TIMER0_Elapse(unsigned int lastRead){
	return TIMER0->TC - lastRead;
}



