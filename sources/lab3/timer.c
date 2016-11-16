/**
* @file		timer.c
* @brief	Contains API source code for controlling timer 0.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/
#include <timer.h>
#include <clock.h>

static uint32_t __freq;

void TIMER0_Init(unsigned int frequency){	

	TIMER0->TCR = TIMER_CR; // disable timer and reset
	TIMER0->PC = 0;			// reset prescale counter
	TIMER0->CTCR = 0; 		// Timer mode

	if(!frequency) frequency = 1;
	if(frequency > CCLK) frequency = CCLK;
	__freq = frequency;
	TIMER0->PR = (getPclk() / frequency) - 1; // pr = pclk / frequency, pclk = cclk / vpdiv (default 4)
	
	TIMER0->TCR = TIMER_CE;	//start timer
}


unsigned int TIMER0_GetValue(void){
	return TIMER0->TC;
}

unsigned int TIMER0_Elapse(unsigned int lastRead){
	return TIMER0->TC - lastRead;
}

//PR+1  => 1000Ms
//ticks => xMs
unsigned int TicksToMs(unsigned int ticks){
return (ticks * MS_IN_1S) / __freq;
}

//FIXME if ms < 1000/freq, the timer
// has no precision to do a precise delay
//workarrond avoid init timer0 with a frequency lower than 1kz
void TIMER0_DelayMs(unsigned int ms){
uint32_t ticks = TIMER0_GetValue();
   while( TicksToMs(TIMER0_Elapse(ticks)) < ms);
}


