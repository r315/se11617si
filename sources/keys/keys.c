#include <gpio.h>

B_STATE _bstate;

uint32_t readKeys(void){
uint32_t _bstate.cur = GPIO_Read() & B_MASK;
	
	if(_bstate.cur == B_MASK){
		if(_bstate.hold == ON)
			_bstate.hold = OFF;
		_bstate.cur = B_EMPTY;
		return B_EMPTY;
	}
	
	if(_bstate.cur != _bstate.last){
		_bstate.last = _bstate.cur;
		_bstate.count = timeNow() + B_HOLD_TIME;
		return cur;
	}
	
	if(timeNow() > _bstate.count){
		_bstate.hold = ON;
	}	
	return _bstate.cur;
}

uint32_t readLastKey(void){
	return _bstate.last;
}
