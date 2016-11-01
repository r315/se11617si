#include <keys.h>

B_STATE _bstate;

uint32_t readKeys(void){
uint32_t cur = GPIO_Read() & B_MASK;
	
	if(cur == B_MASK){		
		if(_bstate.hold == ON)
			_bstate.hold = OFF;			
		if(_bstate.cur != B_EMPTY){
			_bstate.last= _bstate.cur;
			_bstate.cur = B_EMPTY;
		}		
		return B_EMPTY;
	}
	
	_bstate.last = _bstate.cur;
	_bstate.cur = cur;
	
	if(_bstate.cur != _bstate.last){		
		_bstate.count = timeNow() + B_HOLD_TIME;
		return _bstate.cur;
	}
	
	if(timeNow() > _bstate.count){
		_bstate.hold = ON;
	}	
	return _bstate.cur;
}

uint32_t readCurrentKey(void){
	return _bstate.cur;
}

uint32_t readLastKey(void){
	return _bstate.last;
}

uint32_t isKeyHold(void){
	return _bstate.hold;
}

