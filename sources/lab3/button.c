/**
* @file		buttons.C
* @brief	Contains API source code for reading buttons.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/
#include <button.h>
#include <timer.h>
#include <gpio.h>


static BUTTON_Controller __button;

uint32_t BUTTON_Capture(void){
	return (~GPIO_Read()) & BUTTON_MASK;  //common ground
}

void BUTTON_Init(int ht){    
    __button.cur  = BUTTON_EMPTY;
    __button.last = BUTTON_EMPTY;
    __button.events = BUTTON_EMPTY;
    __button.htime = ht;
    GPIO_SetInputN(BUTTON_MASK);
}

int BUTTON_Hit(void){
uint32_t cur = BUTTON_Capture();
	
	// check if any buttons pressed
	if(cur == BUTTON_EMPTY){		
		//update lastkey pressed and events
		if(__button.cur != BUTTON_EMPTY){
			__button.last= __button.cur;
			__button.cur = BUTTON_EMPTY;
			__button.events = BUTTON_RELEASED;
		}
		return BUTTON_EMPTY;
	}
	//update lastkey pressed
	__button.last = __button.cur;
	__button.cur = cur;

	// if not the same key pressed, start timer
	if(__button.cur != __button.last){		
		__button.counter = TIMER0_GetValue();
		__button.events = BUTTON_PRESSED;
		return __button.cur;
	}
	
	//check for timeout and activate hold flag
	if(TicksToMs(TIMER0_Elapse(__button.counter)) > __button.htime){
		__button.events = BUTTON_HOLD;
	}
	else
		__button.events = BUTTON_TIMING;
	
	return __button.cur;
}

int BUTTON_Read(void){
	while(BUTTON_Hit() == BUTTON_EMPTY);
	return __button.cur; 
}

int BUTTON_GetButtonEvents(void){	
	return __button.events;
}

int BUTTON_GetButton(void){
	return __button.cur;
}

void BUTTON_SetHoldTime(int t){
    __button.htime = t;
}



