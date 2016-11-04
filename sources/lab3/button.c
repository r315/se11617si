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


BUTTON_Controller __buttons;

uint32_t BUTTON_Capture(void){
	return (~GPIO0->PIN) & __buttons.mask;  //common ground
}

void BUTTON_Init(uint32_t mask){
	__buttons.cur  = BUTTON_EMPTY;
	__buttons.last = BUTTON_EMPTY;
	__buttons.events = BUTTON_EMPTY;
	__buttons.mask = mask;

	GPIO0->DIR &= ~mask;
}

int BUTTON_Hit(void){
uint32_t cur = BUTTON_Capture();
	
	// check if any buttons pressed
	if(cur == BUTTON_EMPTY){		
		//update lastkey pressed and events
		if(__buttons.cur != BUTTON_EMPTY){
			__buttons.last= __buttons.cur;
			__buttons.cur = BUTTON_EMPTY;
			__buttons.events = BUTTON_RELEASED;
		}
		return BUTTON_EMPTY;
	}
	//update lastkey pressed
	__buttons.last = __buttons.cur;
	__buttons.cur = cur;

	// if not the same key pressed, start timer
	if(__buttons.cur != __buttons.last){		
		__buttons.timer = TIMER0_GetValue();
		__buttons.events = BUTTON_PRESSED;
		return __buttons.cur;
	}
	
	//check for timeout and activate hold flag
	if(TIMER0_Elapse(__buttons.timer) > BUTTON_HOLD_TIME){
		__buttons.events = BUTTON_HOLD;
	}
	
	return __buttons.cur;
}

int BUTTON_Read(void){
	while(BUTTON_Hit() == BUTTON_EMPTY);
	return __buttons.cur; 
}

int BUTTON_GetButtonsEvents(void){
		BUTTON_Hit();
	return __buttons.events;
}




