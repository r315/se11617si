#include <clock.h>

static __pclkval = 0;
static __cclkval = 0;

uint32_t getPclk(void){
	if(!__pclkval)
	   switch(SC->APBDIV & 3){
	      default:
	      case 0: __pclkval = getCclk() / 4; break;
	      case 1: __pclkval = getCclk(); break;
	      case 2: __pclkval = getCclk() / 2; break;
   		}
	return __pclkval;
}

uint32_t getCclk(void){
	__cclkval = XTAL;
	return __cclkval;
}
